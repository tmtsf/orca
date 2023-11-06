#pragma once

#include "experiment/lazy/experiment.hpp"
#include "experiment/lazy/nodes/summation.hpp"
#include "experiment/lazy/nodes/multiplication.hpp"
#include "experiment/lazy/nodes/logarithm.hpp"
#include "experiment/lazy/nodes/leaf.hpp"

namespace orca { namespace experiment { namespace lazy {
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
} } }
