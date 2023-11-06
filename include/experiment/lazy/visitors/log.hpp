#pragma once

#include "experiment/lazy/visitor.hpp"
#include "experiment/lazy/node.hpp"

namespace orca { namespace experiment { namespace lazy {
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
