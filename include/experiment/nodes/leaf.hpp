#pragma once

#include "experiment/experiment.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class Leaf : public Node
    {
    public:
      Leaf(double value);
      virtual double getValue(void) const override;
      virtual void setValue(double value) override;
    private:
      void accept(Visitor& v) const;
    private:
      double m_Value;
    };
  }
}
