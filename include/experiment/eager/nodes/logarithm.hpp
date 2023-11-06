#pragma once

#include "experiment/eager/eager.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  class Logarithm : public Node
  {
  public:
    Logarithm(const node_ptr_t& arg);
    virtual void propagateAdjoint(void) override;
  };
} } }
