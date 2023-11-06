#pragma once

#include "experiment/eager/experiment.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  class Summation : public Node
  {
  public:
    Summation(const node_ptr_t& lhs, const node_ptr_t& rhs);
  private:
    void accept(Visitor& v) const;
  };
} } }
