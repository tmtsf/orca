#include "experiment/lazy/nodes/logarithm.hpp"
#include "experiment/lazy/node.hpp"
#include "experiment/lazy/visitor.hpp"

namespace orca { namespace experiment { namespace lazy {
  Logarithm::Logarithm(const node_ptr_t& arg) :
      Node({arg})
  { }

  void Logarithm::accept(Visitor& v) const
  {
    return v.visit(*this);
  }
} } }
