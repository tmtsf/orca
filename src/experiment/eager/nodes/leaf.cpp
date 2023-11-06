#include "experiment/eager/nodes/leaf.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  Leaf::Leaf(dbl_t value)
  {
    m_Result = value;
  }

  dbl_t Leaf::getValue(void) const
  {
    return m_Result;
  }

  void Leaf::setValue(dbl_t value)
  {
    m_Result = value;
  }

  void Leaf::propagateAdjoint(void)
  {
    // no-op
  }
} } }
