#pragma once

#include "experiment/visitor.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class AdjointVisitor : public Visitor
    {
    public:
      AdjointVisitor(const value_map_t& values);
    public:
      virtual void visit(const Summation& n) override;
      virtual void visit(const Multiplication& n) override;
      virtual void visit(const Logarithm& n) override;
      virtual void visit(const Leaf& n) override;

      dbl_t getResult(void) const;
      const adjoint_map_t& ajoints(void) const;
    private:
      void initializeAdjointIfNecessary(size_t id);
    private:
      adjoint_t m_Adjoint;
      adjoint_map_t m_Adjoints;
      value_map_t m_Values;
      bool m_Root;
    };
  }
}
