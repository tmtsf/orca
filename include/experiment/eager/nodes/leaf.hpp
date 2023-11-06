#pragma once

#include "experiment/eager/experiment.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
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
