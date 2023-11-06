#include "experiment/eager/visitors/evaluation.hpp"

#include <iostream>

namespace orca { namespace experiment { namespace eager {
    EvaluationVisitor::EvaluationVisitor(void) :
      m_Result(0.)
    { }

    void EvaluationVisitor::visit(const Summation& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
      {
        m_Result = m_Visited[id];
        return;
      }

      n.children()[0]->accept(*this);
      dbl_t temp = m_Result;

      n.children()[1]->accept(*this);
      m_Result += temp;

      m_Visited[id] = m_Result;
      // std::cout << id << ": " << m_Result << std::endl;
    }

    void EvaluationVisitor::visit(const Multiplication& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
      {
        m_Result = m_Visited[id];
        return;
      }

      n.children()[0]->accept(*this);
      dbl_t temp = m_Result;

      n.children()[1]->accept(*this);
      m_Result *= temp;

      m_Visited[id] = m_Result;
      // std::cout << id << ": " << m_Result << std::endl;
    }

    void EvaluationVisitor::visit(const Logarithm& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
      {
        m_Result = m_Visited[id];
        return;
      }

      n.children()[0]->accept(*this);
      m_Result = std::log(m_Result);

      m_Visited[id] = m_Result;
      // std::cout << id << ": " << m_Result << std::endl;
    }

    void EvaluationVisitor::visit(const Leaf& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
      {
        m_Result = m_Visited[id];
        return;
      }

      m_Result = n.getValue();

      m_Visited[id] = m_Result;
      // std::cout << id << ": " << m_Result << std::endl;
    }

    dbl_t EvaluationVisitor::getResult(void) const
    {
      return m_Result;
    }

    value_map_t EvaluationVisitor::values(void) const
    {
      return m_Visited;
    }
} } }
