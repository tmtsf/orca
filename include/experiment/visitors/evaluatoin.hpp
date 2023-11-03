#pragma once

#include "experiment/visitor.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class EvaluationVisitor : public Visitor<double>
    {
    public:
      virtual double visit(Summation& n) const
      {
        return n.children()[0]->accept(*this) + n.children()[1]->accept(*this);
      }
      virtual double visit(Multiplication& n) const
      {
        return n.children()[0]->accept(*this) * n.children()[1]->accept(*this);
      }
      virtual double visit(Logarithm& n) const
      {
        return std::log(n.children()[0]->accept(*this));
      }
      virtual double visit(Leaf& n) const
      {
        return n.getValue();
      }
    };
  }
}
