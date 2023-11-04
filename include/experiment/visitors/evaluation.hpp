#pragma once

#include "experiment/visitor.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class EvaluationVisitor : public Visitor
    {
    public:
      EvaluationVisitor(void);
    public:
      virtual void visit(const Summation& n) override;
      virtual void visit(const Multiplication& n) override;
      virtual void visit(const Logarithm& n) override;
      virtual void visit(const Leaf& n) override;

      double getResult(void) const;
    private:
      double m_Result;
      visited_node_value_map_t m_Visited;
    };
  }
}
