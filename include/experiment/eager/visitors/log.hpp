#pragma once

#include "experiment/eager/visitor.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
    class LogVisitor : public Visitor
    {
    public:
      virtual void visit(const Summation& n) override;
      virtual void visit(const Multiplication& n) override;
      virtual void visit(const Logarithm& n) override;
      virtual void visit(const Leaf& n) override;
    private:
      value_map_t m_Visited;
    };
} } }
