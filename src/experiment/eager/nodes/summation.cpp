#include "experiment/eager/nodes/summation.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  Summation::Summation(const node_ptr_t& lhs, const node_ptr_t& rhs) :
    Node({lhs, rhs})
  {
    m_Result = lhs->result() + rhs->result();
  }

  void Summation::propagateAdjoint(void)
  {
    m_Nodes[0]->adjoint() += m_Adjoint;
    m_Nodes[1]->adjoint() += m_Adjoint;
  }
} } }
