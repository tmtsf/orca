#pragma once

#include "experiment/lazy/experiment.hpp"
#include "experiment/lazy/node.hpp"

namespace orca { namespace experiment { namespace lazy {
  class Logarithm : public Node
  {
  public:
    Logarithm(const node_ptr_t& arg);
  private:
    void accept(Visitor& v) const;
  };
} } }
