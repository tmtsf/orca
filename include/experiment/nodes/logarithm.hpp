#pragma once

#include "experiment/experiment.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class Logarithm : public Node
    {
    public:
      Logarithm(const node_ptr_t& arg);
    private:
      template<typename R>
      R accept(const Visitor<R>& v) const;
    };
  }
}
