#pragma once

#include "experiment/eager/eager.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  class Leaf : public Node
  {
  public:
    Leaf(dbl_t value);
    virtual dbl_t getValue(void) const override;
    virtual void setValue(dbl_t value) override;
    virtual void propagateAdjoint(void) override;
  };
} } }
