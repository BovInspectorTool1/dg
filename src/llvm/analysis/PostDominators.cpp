// ignore unused parameters in LLVM libraries
#if (__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <llvm/IR/Function.h>
#include <llvm/Analysis/PostDominators.h>

#if (__clang__)
#pragma clang diagnostic pop // ignore -Wunused-parameter
#else
#pragma GCC diagnostic pop
#endif

#include "analysis/BFS.h"
#include "analysis/PostDominanceFrontiers.h"

#include "llvm/LLVMDependenceGraph.h"

namespace dg {

void LLVMDependenceGraph::computePostDominators(bool addPostDomFrontiers)
{
    using namespace llvm;
    // iterate over all functions
    for (auto& F : getConstructedFunctions()) {
        analysis::PostDominanceFrontiers<LLVMNode> pdfrontiers;

        // root of post-dominator tree
        LLVMBBlock *root = nullptr;
        Value *val = const_cast<Value *>(F.first);
        Function& f = *cast<Function>(val);
        PostDominatorTree *pdtree;

#if ((LLVM_VERSION_MAJOR == 3) && (LLVM_VERSION_MINOR < 9))
        pdtree = new PostDominatorTree();
        // compute post-dominator tree for this function
        pdtree->runOnFunction(f);
#else
        PostDominatorTreeAnalysis PDT;
        FunctionAnalysisManager DummyFAM;
        pdtree = new PostDominatorTree(PDT.run(f, DummyFAM));
#endif

        // add immediate post-dominator edges
        auto& our_blocks = F.second->getBlocks();
        bool built = false;
        for (auto& it : our_blocks) {
            LLVMBBlock *BB = it.second;
            BasicBlock *B = cast<BasicBlock>(const_cast<Value *>(it.first));
            DomTreeNode *N = pdtree->getNode(B);
            // when function contains infinite loop, we're screwed
            // and we don't have anything
            // FIXME: just check for the root,
            // don't iterate over all blocks, stupid...
            if (!N)
                continue;

            DomTreeNode *idom = N->getIDom();
            BasicBlock *idomBB = idom ? idom->getBlock() : nullptr;
            built = true;

            if (idomBB) {
                LLVMBBlock *pb = our_blocks[idomBB];
                assert(pb && "Do not have constructed BB");
                BB->setIPostDom(pb);
                assert(cast<BasicBlock>(BB->getKey())->getParent()
                        == cast<BasicBlock>(pb->getKey())->getParent()
                        && "BBs are from diferent functions");
            // if we do not have idomBB, then the idomBB is a root BB
            } else {
                // PostDominatorTree may has special root without BB set
                // or it is the node without immediate post-dominator
                if (!root) {
                    root = new LLVMBBlock();
                    root->setKey(nullptr);
                    F.second->setPostDominatorTreeRoot(root);
                }

                BB->setIPostDom(root);
            }
        }

        // well, if we haven't built the pdtree, this is probably infinite loop
        // that has no pdtree. Until we have anything better, just add sound control
        // edges that are not so precise - to predecessors.
        if (!built && addPostDomFrontiers) {
            for (auto& it : our_blocks) {
                LLVMBBlock *BB = it.second;
                for (const LLVMBBlock::BBlockEdge& succ : BB->successors()) {
                    // in this case we add only the control dependencies,
                    // since we have no pd frontiers
                    BB->addControlDependence(succ.target);
                }
            }
        }

        if (addPostDomFrontiers) {
            // assert(root && "BUG: must have root");
            if (root)
                pdfrontiers.compute(root, true /* store also control depend. */);
        }

        delete pdtree;
    }
}

} // namespace dg
