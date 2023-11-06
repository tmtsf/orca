#pragma once

#include "experiment/eager/visitor.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
    class EvaluationVisitor : public Visitor
    {
    public:
      EvaluationVisitor(void);
    public:
      virtual void visit(const Summation& n) override;
      virtual void visit(const Multiplication& n) override;
      virtual void visit(const Logarithm& n) override;
      virtual void visit(const Leaf& n) override;

      dbl_t getResult(void) const;
      value_map_t values(void) const;
    private:
      dbl_t m_Result;
      value_map_t m_Visited;
    };
} } }
