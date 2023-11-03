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

    void Logarithm::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
  }
}
