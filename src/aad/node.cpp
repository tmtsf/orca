#include "aad/node.hpp"
#include "math/util.hpp"

namespace orca { namespace aad {
  Node::Node(void) :
    Node(0)
  { }

  Node::Node(size_t arity) :
    m_Arity(arity),
    m_SelfAdjoint(0.)
  { }

  adjoint_t& Node::adjoint(void)
  {
    return m_SelfAdjoint;
  }

  void Node::propagateOne(void)
  {
    if (m_Arity == 0 || math::util::isZeroToMachineTolerance(m_SelfAdjoint))
      return;

    for (size_t i = 0; i < m_Arity; ++i)
    {
      *(m_ChildrenAdjoints[i]) += m_DerivativesToChildren[i] * m_SelfAdjoint;
    }
  }
}}
