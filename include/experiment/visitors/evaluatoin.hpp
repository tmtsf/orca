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
      EvaluationVisitor(void) :
        m_Result(0.)
      {}
    public:
      virtual void visit(const Summation& n) override
      {
        n.children()[0]->accept(*this);
        double temp = m_Result;

        n.children()[1]->accept(*this);
        m_Result += temp;
      }
      virtual void visit(const Multiplication& n) override
      {
        n.children()[0]->accept(*this);
        double temp = m_Result;

        n.children()[1]->accept(*this);
        m_Result *= temp;
      }
      virtual void visit(const Logarithm& n) override
      {
        n.children()[0]->accept(*this);
        m_Result = std::log(m_Result);
      }
      virtual void visit(const Leaf& n) override
      {
        m_Result = n.getValue();
      }
      double getResult(void) const
      {
        return m_Result;
      }
    private:
      double m_Result;
    };
  }
}
