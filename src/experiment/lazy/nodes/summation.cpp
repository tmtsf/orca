#include "experiment/lazy/nodes/summation.hpp"
#include "experiment/lazy/node.hpp"
#include "experiment/lazy/visitor.hpp"

namespace orca { namespace experiment { namespace lazy {
    Summation::Summation(const node_ptr_t& lhs, const node_ptr_t& rhs) :
        Node({lhs, rhs})
    { }

    void Summation::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
} } }
