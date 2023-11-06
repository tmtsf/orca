#include "experiment/lazy/nodes/leaf.hpp"
#include "experiment/lazy/node.hpp"
#include "experiment/lazy/visitor.hpp"

namespace orca { namespace experiment { namespace lazy {
  Leaf::Leaf(dbl_t value) :
    Node({}),
    m_Value(value)
  { }

  void Leaf::accept(Visitor& v) const
  {
    return v.visit(*this);
  }

  dbl_t Leaf::getValue(void) const
  {
    return m_Value;
  }

  void Leaf::setValue(dbl_t value)
  {
    m_Value = value;
  }
} } }
