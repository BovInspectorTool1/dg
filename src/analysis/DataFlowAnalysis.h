#ifndef _DG_DATA_FLOW_ANALYSIS_H_
#define _DG_DATA_FLOW_ANALYSIS_H_

#include <utility>
#include <set>

#include "Analysis.h"
#include "DFS.h"

#ifndef ENABLE_CFG
#error "Need CFG enabled for data flow analysis"
#endif

namespace dg {
namespace analysis {

struct DataFlowStatistics : public AnalysisStatistics {
    DataFlowStatistics()
        : AnalysisStatistics(), bblocksNum(0), iterationsNum(0) {}

    uint64_t bblocksNum;
    uint64_t iterationsNum;

    uint64_t getBBlocksNum() const { return bblocksNum; }
    uint64_t getIterationsNum() const { return iterationsNum; }
};

enum DataFlowAnalysisFlags {
    DATAFLOW_INTERPROCEDURAL    = 1 << 0,
    DATAFLOW_BB_NO_CALLSITES    = 1 << 1,
};

// ordering of nodes with respect to DFS order
// works for both nodes and blocks
template<typename T>
struct DFSOrderLess
{
    bool operator()(T a, T b) const
    {
        return a->getDFSOrder() < b->getDFSOrder();
    }
};

template <typename NodeT>
class BBlockDataFlowAnalysis : public Analysis<NodeT>
{
public:
    BBlockDataFlowAnalysis<NodeT>(BBlock<NodeT> *entryBB, uint32_t fl = 0)
        :entryBB(entryBB), flags(fl) {}

    virtual bool runOnBlock(BBlock<NodeT> *BB) = 0;

    void run()
    {
        bool changed = false;
        uint32_t flg = 0;
        BlocksSetT blocks;

        assert(entryBB && "entry basic block is nullptr");

        /* translate flags */
        if (flags & DATAFLOW_INTERPROCEDURAL)
            flg |= DFS_INTERPROCEDURAL;
        if (flags & DATAFLOW_BB_NO_CALLSITES)
            flg |= DFS_BB_NO_CALLSITES;

        BBlockDFS<NodeT> DFS(flg);
        DFSDataT data(blocks, changed, this);

        // we will get all the nodes using DFS
        DFS.run(entryBB, dfs_proc_bb, data);

        // update statistics
        statistics.bblocksNum = blocks.size();
        statistics.iterationsNum = 1;
        // first run goes over each BB once
        statistics.processedBlocks = statistics.bblocksNum;

        // Iterate over the nodes in dfs reverse order, it is
        // usually good for reaching fixpoint. Later we can
        // add options what ordering to use.
        // Since we used while loop, if nothing changed after the
        // first iteration (the DFS), the loop will never run
        while (changed) {
            changed = false;
            for (auto I = blocks.rbegin(), E = blocks.rend();
                 I != E; ++I) {
                changed |= runOnBlock(*I);
                ++statistics.processedBlocks;
            }

            ++statistics.iterationsNum;
        }
    }

    uint32_t getFlags() const { return flags; }

    const DataFlowStatistics& getStatistics() const
    {
        return statistics;
    }

private:
    // define set of blocks to be ordered in dfs order
    typedef std::set<BBlock<NodeT> *,
                     DFSOrderLess<BBlock<NodeT> *>> BlocksSetT;
    struct DFSDataT
    {
        DFSDataT(BlocksSetT& b, bool& c, BBlockDataFlowAnalysis<NodeT> *r)
            :blocks(b), changed(c), ref(r) {}

        BlocksSetT& blocks;
        bool& changed;
        BBlockDataFlowAnalysis<NodeT> *ref;
    };

    static void dfs_proc_bb(BBlock<NodeT> *BB,
                            DFSDataT& data)
    {
        data.changed |= data.ref->runOnBlock(BB);
        data.blocks.insert(BB);
    }

    BBlock<NodeT> *entryBB;
    uint32_t flags;
    DataFlowStatistics statistics;
};


template <typename NodeT>
class DataFlowAnalysis : public BBlockDataFlowAnalysis<NodeT>
{
public:
    DataFlowAnalysis<NodeT>(BBlock<NodeT> *entryBB, uint32_t fl = 0)
        : BBlockDataFlowAnalysis<NodeT>(entryBB, fl) {};

    /* virtual */
    bool runOnBlock(BBlock<NodeT> *B)
    {
        bool changed = false;
        NodeT *n = B->getFirstNode();

        while(n) {
            changed |= runOnNode(n);
            n = n->getSuccessor();
        }

        return changed;
    }

    virtual bool runOnNode(NodeT *n) = 0;

private:
};

} // namespace analysis
} // namespace dg

#endif //  _DG_DATA_FLOW_ANALYSIS_H_
