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
    private:
      template<typename R>
      R accept(const Visitor<R>& v) const;
    private:
      double m_Value;
    };
  }
}
