#pragma once

#include "experiment/eager/eager.hpp"

namespace orca { namespace experiment { namespace eager {
  class Number
  {
  public:
    Number(void) = default;
    Number(dbl_t value);
    Number(const node_ptr_t& node);
  public:
    const node_ptr_t& node(void) const;
    dbl_t getValue(void) const;
    void setValue(dbl_t value);

    value_t result(void) const;
    adjoint_t& adjoint(void);
    void propagateAdjoints(void);
  public:
    static tape_t m_Tape;
  private:
    node_ptr_t m_Node;
  };
} } }
