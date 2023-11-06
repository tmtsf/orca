#pragma once

#include "experiment/eager/experiment.hpp"
#include "experiment/eager/nodes/summation.hpp"
#include "experiment/eager/nodes/multiplication.hpp"
#include "experiment/eager/nodes/logarithm.hpp"
#include "experiment/eager/nodes/leaf.hpp"

namespace orca { namespace experiment { namespace eager {
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
