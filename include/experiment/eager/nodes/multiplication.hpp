#pragma once

#include "experiment/eager/eager.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  class Multiplication : public Node
  {
  public:
    Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs);
    virtual void propagateAdjoint(void) override;
  };
} } }
