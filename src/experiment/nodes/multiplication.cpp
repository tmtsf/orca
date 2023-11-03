#include "experiment/nodes/multiplication.hpp"
#include "experiment/node.hpp"
#include "experiment/visitor.hpp"

namespace orca
{
  namespace experiment
  {
    Multiplication::Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs) :
        Node({lhs, rhs})
    { }

    template<typename R>
    R Multiplication::accept(const Visitor<R>& v) const
    {
      return v.visit(*this);
    }
  }
}
