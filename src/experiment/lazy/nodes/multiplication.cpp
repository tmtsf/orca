#include "experiment/lazy/nodes/multiplication.hpp"
#include "experiment/lazy/node.hpp"
#include "experiment/lazy/visitor.hpp"

namespace orca { namespace experiment { namespace lazy {
    Multiplication::Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs) :
        Node({lhs, rhs})
    { }

    void Multiplication::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
} } }
