#pragma once

#include "aad/aad.hpp"

namespace orca { namespace aad{
  class Number;
  class Tape;

  class Node
  {
    friend Number;
    friend Tape;
  public:
    Node(void);
    Node(size_t arity);
    adjoint_t& adjoint(void);
    void propagateOne(void);
  private:
    size_t m_Arity;
    adjoint_t m_SelfAdjoint;
    derivative_coll_t m_DerivativesToChildren;
    adjoint_ptr_coll_t m_ChildrenAdjoints;
  };
}}
