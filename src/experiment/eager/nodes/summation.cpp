#include "experiment/eager/nodes/summation.hpp"
#include "experiment/eager/node.hpp"
#include "experiment/eager/visitor.hpp"

namespace orca { namespace experiment { namespace eager {
    Summation::Summation(const node_ptr_t& lhs, const node_ptr_t& rhs) :
        Node({lhs, rhs})
    { }

    void Summation::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
} } }
