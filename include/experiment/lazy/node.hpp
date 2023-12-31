#pragma once

#include "experiment/lazy/lazy.hpp"

namespace orca { namespace experiment { namespace lazy {
  class Node
  {
  public:
    virtual ~Node(void) = default;
  protected:
    Node(const node_ptr_coll_t& nodes);
  public:
    const node_ptr_coll_t& children(void) const;
    size_t id(void) const;

    virtual dbl_t getValue(void) const;
    virtual void setValue(dbl_t value);

    virtual void accept(Visitor&) const = 0;
  protected:
    node_ptr_coll_t m_Nodes;
    static size_t m_Count;
    size_t m_ID;
  };

  node_ptr_t makeLeafNode(dbl_t value);
  node_ptr_t operator+(const Number& lhs, const Number& rhs);
  node_ptr_t operator*(const Number& lhs, const Number& rhs);
  node_ptr_t log(const Number& arg);
} } }
