#include "experiment/nodes/leaf.hpp"
#include "experiment/node.hpp"
#include "experiment/visitor.hpp"

namespace orca
{
  namespace experiment
  {
    Leaf::Leaf(double value) :
      Node({}),
      m_Value(value)
    { }

    void Leaf::accept(Visitor& v) const
    {
      return v.visit(*this);
    }

    double Leaf::getValue(void) const
    {
      return m_Value;
    }

    void Leaf::setValue(double value)
    {
      m_Value = value;
    }
  }
}
