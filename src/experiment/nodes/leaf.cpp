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

    template<typename R>
    R Leaf::accept(const Visitor<R>& v) const
    {
      return v.visit(*this);
    }
  }
}
