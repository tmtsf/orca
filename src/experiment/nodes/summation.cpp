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

    void Summation::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
  }
}
