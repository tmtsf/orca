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
    class Visitor
    {
    public:
      virtual ~Visitor(void) = default;
    public:
      virtual void visit(const Summation&) = 0;
      virtual void visit(const Multiplication&) = 0;
      virtual void visit(const Logarithm&) = 0;
      virtual void visit(const Leaf&) = 0;
    };
  }
}
