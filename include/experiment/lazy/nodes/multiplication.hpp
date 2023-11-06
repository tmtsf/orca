#pragma once

#include "experiment/lazy/experiment.hpp"
#include "experiment/lazy/node.hpp"

namespace orca { namespace experiment { namespace lazy {
  class Multiplication : public Node
  {
  public:
    Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs);
  private:
    void accept(Visitor& v) const;
  };
} } }
