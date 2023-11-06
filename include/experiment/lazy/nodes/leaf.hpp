#pragma once

#include "experiment/lazy/experiment.hpp"
#include "experiment/lazy/node.hpp"

namespace orca { namespace experiment { namespace lazy {
  class Leaf : public Node
  {
  public:
    Leaf(dbl_t value);
    virtual dbl_t getValue(void) const override;
    virtual void setValue(dbl_t value) override;
  private:
    void accept(Visitor& v) const;
  private:
    dbl_t m_Value;
  };
} } }
