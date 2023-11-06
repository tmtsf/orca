#include "experiment/eager/number.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  tape_t Number::m_Tape;

  Number::Number(dbl_t value) :
    m_Node(makeLeafNode(value))
  {
    m_Tape.emplace_back(m_Node);
  }

  Number::Number(const node_ptr_t& node) :
    m_Node(node)
  {  }

  const node_ptr_t& Number::node(void) const
  {
    return m_Node;
  }

  dbl_t Number::getValue(void) const
  {
    return m_Node->getValue();
  }

  void Number::setValue(dbl_t value)
  {
    m_Node->setValue(value);
  }

  value_t Number::result(void) const
  {
    return m_Node->result();
  }

  adjoint_t& Number::adjoint(void)
  {
    return m_Node->adjoint();
  }

  void Number::propagateAdjoints(void)
  {
    m_Node->resetAdjoints();
    m_Node->adjoint() = 1.;

    auto it = m_Tape.rbegin();
    while (it->get() != m_Node)
      ++it;

    while (it != m_Tape.rend())
    {
      (*it)->propagateAdjoint();
      ++it;
    }
  }
} } }
