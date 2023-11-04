#pragma once

#include "experiment/visitor.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class LogVisitor : public Visitor
    {
    public:
      virtual void visit(const Summation& n) override;
      virtual void visit(const Multiplication& n) override;
      virtual void visit(const Logarithm& n) override;
      virtual void visit(const Leaf& n) override;
    private:
      visited_node_map_t m_Visited;
    };
  }
}
