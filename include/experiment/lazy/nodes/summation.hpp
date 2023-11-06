#pragma once

#include "experiment/lazy/lazy.hpp"
#include "experiment/lazy/node.hpp"

namespace orca { namespace experiment { namespace lazy {
  class Summation : public Node
  {
  public:
    Summation(const node_ptr_t& lhs, const node_ptr_t& rhs);
  private:
    void accept(Visitor& v) const;
  };
} } }
