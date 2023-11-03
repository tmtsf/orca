#include "experiment/nodes/summation.hpp"
#include "experiment/node.hpp"
#include "experiment/visitor.hpp"

namespace orca
{
  namespace experiment
  {
    Summation::Summation(const node_ptr_t& lhs, const node_ptr_t& rhs) :
        Node({lhs, rhs})
    { }

    template<typename R>
    R Summation::accept(const Visitor<R>& v) const
    {
      return v.visit(*this);
    }
  }
}
