#pragma once

#include "experiment/experiment.hpp"

namespace orca
{
  namespace experiment
  {
    class Number
    {
    public:
      Number(dbl_t value);
      Number(const node_ptr_t& node);
    public:
      const node_ptr_t& node(void) const;
      dbl_t getValue(void) const;
      void setValue(dbl_t value);

      dbl_t calculate(void) const;
      void printLog(void) const;
      const value_map_t& adjoints(void) const;
    private:
      node_ptr_t m_Node;
      mutable value_map_t m_Values;
      mutable adjoint_map_t m_Adjoints;
    };
  }
}
