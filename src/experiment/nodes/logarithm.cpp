#include "experiment/nodes/logarithm.hpp"
#include "experiment/node.hpp"
#include "experiment/visitor.hpp"

namespace orca
{
  namespace experiment
  {
    Logarithm::Logarithm(const node_ptr_t& arg) :
        Node({arg})
    { }

    template<typename R>
    R Logarithm::accept(const Visitor<R>& v) const
    {
      return v.visit(*this);
    }
  }
}
