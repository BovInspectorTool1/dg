#ifndef _DG_NODES_WALK_H_
#define _DG_NODES_WALK_H_

#include "Analysis.h"

namespace dg {
namespace analysis {

static unsigned int walk_run_counter;

template <typename NodePtrT, typename QueueT>
class NodesWalk : Analysis<NodePtrT>
{
public:
    template <typename FuncT, typename DataT>
    void walk(NodePtrT entry, FuncT func, DataT data,
              bool control = true, bool deps = true)
    {
        unsigned int run_id = ++walk_run_counter;
        QueueT queue;

        assert(entry && "Need entry node for traversing nodes");

        AnalysesAuxiliaryData& aad = this->getAnalysisData(entry);
        aad.lastwalkid = run_id;

        queue.push(entry);

        while (!queue.empty()) {
            NodePtrT n = queue.front();
            queue.pop();

            func(n, data);

            // add unprocessed vertices
            if (control)
                processEdges(n->control_begin(),
                             n->control_end(), queue, run_id);

            if (deps)
                processEdges(n->data_begin(),
                             n->data_end(), queue, run_id);
        }
    }

private:
    template <typename IT>
    void processEdges(IT begin, IT end, QueueT& queue,
                      unsigned int run_id)
    {
        for (IT I = begin; I != end; ++I) {
            NodePtrT tmp = *I;
            AnalysesAuxiliaryData& aad = this->getAnalysisData(tmp);
            aad.lastwalkid = run_id;

            if (aad.lastwalkid == run_id)
                continue;

            // mark node as visited
            aad.lastwalkid = run_id;
            queue.push(tmp);
        }
    }

    QueueT queue;
};


#ifdef ENABLE_CFG

#include "../BBlock.h"

template <typename NodePtrT, typename QueueT>
class BBlockWalk : BBlockAnalysis<NodePtrT>
{
public:
    typedef BBlock<NodePtrT> *BBlockPtrT;

    template <typename FuncT, typename DataT>
    void walk(BBlockPtrT entry, FuncT func, DataT data)
    {
        QueueT queue;
        queue.push(entry);

        unsigned int runid = ++walk_run_counter;

        while (!queue.empty()) {
            BBlockPtrT BB = queue.front();
            queue.pop();

            AnalysesAuxiliaryData& aad = this->getAnalysisData(BB);
            aad.lastwalkid = runid;

            func(BB, data);

            for (BBlockPtrT S : BB->successors()) {
                AnalysesAuxiliaryData& sad = this->getAnalysisData(S);
                if (sad.lastwalkid != runid)
                    queue.push(S);
            }
        }
    }
};

#endif

} // namespace analysis
} // namespace dg

#endif // _DG_NODES_WALK_H_
