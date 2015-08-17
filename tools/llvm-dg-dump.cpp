#include <assert.h>
#include <cstdio>

#ifndef HAVE_LLVM
#error "This code needs LLVM enabled"
#endif

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IRReader/IRReader.h>

#include <iostream>
#include "llvm/LLVMDependenceGraph.h"
#include "DG2Dot.h"

using namespace dg;
using llvm::errs;

static std::ostream& printLLVMVal(std::ostream& os, const llvm::Value *val)
{
    llvm::raw_os_ostream ro(os);

    if (!val) {
        ro << "(null)";
        return os;
    }

    if (llvm::isa<llvm::Function>(val))
        ro << "ENTRY " << val->getName();
    else
        // just dump it there
        ro << *val;

    return os;
}

static std::ostream& operator<<(std::ostream& os, const Offset& off)
{
    if (off.offset == UNKNOWN_OFFSET)
        os << "UNKNOWN";
    else
        os << off.offset;
}

static bool checkNode(std::ostream& os, LLVMNode *node)
{
    bool err = false;
    const llvm::Value *val = node->getKey();

    if (!val) {
        os << "\\nERR: no value in node";
        return true;
    }

    if (!node->getBasicBlock()
        && !llvm::isa<llvm::Function>(val)) {
        err = true;
        os << "\\nERR: no BB";
    }

    LLVMNode *s = node->getSuccessor();
    LLVMNode *p = node->getPredcessor();
    if (s) {
        if (s->getPredcessor() != node) {
            os << "\\nERR: wrong predcessor";
            err = true;
        }

        if(s->getBasicBlock() != node->getBasicBlock()) {
            os << "\\nERR: succ BB mismatch";
            err = true;
        }
    }

    if (p) {
        if (p->getSuccessor() != node) {
            os << "\\nERR: wrong successor";
            err = true;
        }

        if(p->getBasicBlock() != node->getBasicBlock()) {
            os << "\\nERR: pred BB mismatch";
            err = true;
        }
    }

    if (node->hasUnknownValue()) {
        os << "\\lUNKNOWN VALUE";
    } else {
        const ValuesSetT& vals = node->getValues();
        for (auto it : vals) {
                os << "\\lVAL: [";
                printLLVMVal(os, it->getKey());
                os << "]";
        }

        const PointsToSetT& ptsto = node->getPointsTo();
        for (auto it : ptsto) {
            os << "\\lPTR: [";
            printLLVMVal(os, it.obj->node->getKey());
            os << "] + " << it.offset;
        }

        MemoryObj *mo = node->getMemoryObj();
        if (mo) {
            for (auto it : mo->values) {
                for (auto it2 : it.second) {
                    os << "\\l--MEMVAL: [" << it.first << "] = ";
                    printLLVMVal(os, it2->getKey());
                }
            }

            for (auto it : mo->pointsTo) {
                for(auto it2 : it.second) {
                    os << "\\l--MEMPTR: [" << it.first << "] -> ";
                    printLLVMVal(os, it2.obj->node->getKey());
                    os << "] + " << it2.offset;
                }
            }
        } else {
            if (llvm::isa<llvm::AllocaInst>(val)) {
                os << "\\nERR: alloca without memObject";
                err = true;
            }
        }
    }

    return err;
}

int main(int argc, char *argv[])
{
    llvm::LLVMContext context;
    llvm::SMDiagnostic SMD;
    std::unique_ptr<llvm::Module> M;
    const char *module = NULL;

    using namespace debug;
    uint32_t opts = PRINT_CFG | PRINT_DD | PRINT_CD;

    // parse options
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-no-control") == 0) {
            opts &= ~PRINT_CD;
        } else if (strcmp(argv[i], "-no-data") == 0) {
            opts &= ~PRINT_DD;
        } else if (strcmp(argv[i], "-cfg") == 0) {
            opts |= PRINT_CFG;
        } else if (strcmp(argv[i], "-call") == 0) {
            opts |= PRINT_CALL;
        } else if (strcmp(argv[i], "-cfgall") == 0) {
            opts |= PRINT_CFG;
            opts |= PRINT_REV_CFG;
        } else if (strcmp(argv[i], "-pd") == 0) {
            errs() << "Not implemented now\n";
        } else {
            module = argv[i];
        }
    }

    if (!module) {
        errs() << "Usage: % IR_module [output_file]\n";
        return 1;
    }

    M = llvm::parseIRFile(module, SMD, context);
    if (!M) {
        SMD.print(argv[0], errs());
        return 1;
    }

    LLVMDependenceGraph d;
    d.build(&*M);

    debug::DG2Dot<LLVMNode> dump(&d, opts);

    dump.printKey = printLLVMVal;
    dump.checkNode = checkNode;

    dump.dump("/dev/stdout", d.getEntryBB());

    return 0;
}
