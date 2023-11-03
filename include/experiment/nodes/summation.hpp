#pragma once

#include "experiment/experiment.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class Summation : public Node
    {
    public:
      Summation(const node_ptr_t& lhs, const node_ptr_t& rhs);
    private:
      void accept(Visitor& v) const;
    };
  }
}
