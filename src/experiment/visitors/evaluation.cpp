#include "experiment/visitors/evaluation.hpp"

namespace orca
{
  namespace experiment
  {
    EvaluationVisitor::EvaluationVisitor(void) :
      m_Result(0.)
    { }

    void EvaluationVisitor::visit(const Summation& n)
    {
      n.children()[0]->accept(*this);
      double temp = m_Result;

      n.children()[1]->accept(*this);
      m_Result += temp;
    }

    void EvaluationVisitor::visit(const Multiplication& n)
    {
      n.children()[0]->accept(*this);
      double temp = m_Result;

      n.children()[1]->accept(*this);
      m_Result *= temp;
    }

    void EvaluationVisitor::visit(const Logarithm& n)
    {
      n.children()[0]->accept(*this);
      m_Result = std::log(m_Result);
    }

    void EvaluationVisitor::visit(const Leaf& n)
    {
      m_Result = n.getValue();
    }

    double EvaluationVisitor::getResult(void) const
    {
      return m_Result;
    }
  }
}
