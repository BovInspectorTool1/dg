#ifndef _DG_ANALYSIS_POINTS_TO_FLOW_INSENSITIVE_H_
#define _DG_ANALYSIS_POINTS_TO_FLOW_INSENSITIVE_H_

#include <cassert>
#include <set>

#include "PSS.h"

namespace dg {
namespace analysis {
namespace pss {

class PointsToFlowInsensitive : public PSS
{
    std::set<PSSNode *> changed;

    // FIXME: we could do common ancestor for this class
    // and PointsToFlowSensitive, since this code is
    // duplicated
    static bool removeFromChanged(PSSNode *n, void *data)
    {
        std::set<PSSNode *> *changed
            = static_cast<std::set<PSSNode *> *>(data);
        assert(changed);

        changed->erase(n);
        return true;
    }

protected:
    PointsToFlowInsensitive() {}

public:
    PointsToFlowInsensitive(PSSNode *r) : PSS(r) {}

    virtual void getMemoryObjects(PSSNode *where, PSSNode *n,
                                  std::vector<MemoryObject *>& objects)
    {
        // irrelevant in flow-insensitive
        (void) where;

        // we want to have memory in allocation sites
        if (n->getType() == pss::CAST || n->getType() == pss::GEP)
            n = n->getOperand(0);
        else if (n->getType() == pss::CONSTANT) {
            assert(n->pointsTo.size() == 1);
            n = (n->pointsTo.begin())->target;
        }

        assert(n->getType() == pss::ALLOC || n->getType() == pss::DYN_ALLOC
               || n->getType() == pss::UNKNOWN_MEM);

        MemoryObject *mo = n->getData<MemoryObject>();
        if (!mo) {
            mo = new MemoryObject(n);
            n->setData<MemoryObject>(mo);
        }

        objects.push_back(mo);
    }

    virtual void enqueue(PSSNode *n)
    {
        changed.insert(n);
    }

    virtual void afterProcessed(PSSNode *n)
    {
        (void) n;

        if (pendingInQueue() == 0 && !changed.empty()) {
            std::set<PSSNode *> nodes;
            getNodes(nodes, removeFromChanged, &changed);

            //FIXME: do it more efficiently
            for (PSSNode *node : nodes)
                queue.push(node);
        }
    }
};

} // namespace pss
} // namespace analysis
} // namespace dg

#endif // _DG_ANALYSIS_POINTS_TO_FLOW_INSENSITIVE_H_

