#pragma once

#include "experiment/experiment.hpp"
#include "experiment/nodes/summation.hpp"
#include "experiment/nodes/multiplication.hpp"
#include "experiment/nodes/logarithm.hpp"
#include "experiment/nodes/leaf.hpp"

namespace orca
{
  namespace experiment
  {
    template<typename R>
    class Visitor
    {
    public:
      virtual ~Visitor(void) = default;
    public:
      virtual R visit(Summation&) const = 0;
      virtual R visit(Multiplication&) const = 0;
      virtual R visit(Logarithm&) const = 0;
      virtual R visit(Leaf&) const = 0;
    };
  }
}
