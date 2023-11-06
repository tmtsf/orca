#include "experiment/eager/nodes/multiplication.hpp"
#include "experiment/eager/node.hpp"
#include "experiment/eager/visitor.hpp"

namespace orca { namespace experiment { namespace eager {
    Multiplication::Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs) :
        Node({lhs, rhs})
    { }

    void Multiplication::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
} } }
