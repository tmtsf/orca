#include "experiment/eager/nodes/leaf.hpp"
#include "experiment/eager/node.hpp"
#include "experiment/eager/visitor.hpp"

namespace orca { namespace experiment { namespace eager {
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
