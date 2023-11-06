#pragma once

#include "experiment/eager/eager.hpp"

namespace orca { namespace experiment { namespace eager {
  class Node
  {
  public:
    Node(void) = default;
    virtual ~Node(void) = default;
  protected:
    Node(const node_ptr_coll_t& nodes);
  public:
    virtual dbl_t getValue(void) const;
    virtual void setValue(dbl_t value);

    value_t result(void) const;
    adjoint_t& adjoint(void);
    void resetAdjoints(void);
    virtual void propagateAdjoint(void) = 0;
  protected:
    node_ptr_coll_t m_Nodes;
    value_t m_Result;
    adjoint_t m_Adjoint;
  };

  node_ptr_t makeLeafNode(dbl_t value);
  Number operator+(const Number& lhs, const Number& rhs);
  Number operator*(const Number& lhs, const Number& rhs);
  Number log(const Number& arg);
} } }
