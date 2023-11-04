#pragma once

#include "experiment/experiment.hpp"

namespace orca
{
  namespace experiment
  {
    class Number
    {
    public:
      Number(double value);
      Number(const node_ptr_t& node);
    public:
      const node_ptr_t& node(void) const;
      double getValue(void) const;
      void setValue(double value);

      double calculate(void) const;
      void printLog(void) const;
    private:
      node_ptr_t m_Node;
    };
  }
}
