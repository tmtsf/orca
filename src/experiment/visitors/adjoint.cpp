#include "experiment/visitors/adjoint.hpp"

#include <iostream>

namespace orca
{
  namespace experiment
  {
    AdjointVisitor::AdjointVisitor(const value_map_t& values) :
      m_Adjoint(0.),
      m_Values(values),
      m_Root(true)
    { }

    void AdjointVisitor::visit(const Summation& n)
    {
      size_t id = n.id();
      initializeAdjointIfNecessary(id);
      dbl_t adjoint = m_Adjoint;
      // std::cout << id << ": " << m_Adjoint << std::endl;

      for (const auto& child : n.children())
      {
        id = child->id();
        m_Adjoints[id] += adjoint;
        m_Adjoint = adjoint;
        child->accept(*this);
      }
    }

    void AdjointVisitor::visit(const Multiplication& n)
    {
      size_t id = n.id();
      initializeAdjointIfNecessary(id);
      dbl_t adjoint = m_Adjoint;
      // std::cout << id << ": " << m_Adjoint << std::endl;

      const auto& childOne = n.children()[0];
      const auto& childTwo = n.children()[1];

      size_t idOne = childOne->id();
      size_t idTwo = childTwo->id();

      m_Adjoint = adjoint * m_Values[idTwo];
      m_Adjoints[idOne] += m_Adjoint;
      childOne->accept(*this);

      m_Adjoint = adjoint * m_Values[idOne];
      m_Adjoints[idTwo] += m_Adjoint;
      childTwo->accept(*this);
    }

    void AdjointVisitor::visit(const Logarithm& n)
    {
      size_t id = n.id();
      initializeAdjointIfNecessary(id);
      dbl_t adjoint = m_Adjoint;
      // std::cout << id << ": " << m_Adjoint << std::endl;

      const auto& child = n.children()[0];
      id = child->id();
      m_Adjoint = adjoint / m_Values[id];
      m_Adjoints[id] += m_Adjoint;
      child->accept(*this);
    }

    void AdjointVisitor::visit(const Leaf& n)
    {
      // no-op
      // std::cout << n.id() << ": " << m_Adjoint << std::endl;
    }

    const adjoint_map_t& AdjointVisitor::ajoints(void) const
    {
      return m_Adjoints;
    }

    void AdjointVisitor::initializeAdjointIfNecessary(size_t id)
    {
      if (m_Root)
      {
        m_Adjoint = 1.;
        m_Adjoints[id] = 1.;
        m_Root = false;
      }
    }
  }
}
