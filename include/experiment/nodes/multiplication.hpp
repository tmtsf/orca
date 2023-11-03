#pragma once

#include "experiment/experiment.hpp"
#include "experiment/node.hpp"

namespace orca
{
  namespace experiment
  {
    class Multiplication : public Node
    {
    public:
      Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs);
    private:
      template<typename R>
      R accept(const Visitor<R>& v) const;
    };
  }
}