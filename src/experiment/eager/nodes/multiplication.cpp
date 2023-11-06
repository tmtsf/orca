#include "experiment/eager/nodes/multiplication.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  Multiplication::Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs) :
      Node({lhs, rhs})
  {
    m_Result = lhs->result() * rhs->result();
  }

  void Multiplication::propagateAdjoint(void)
  {
    m_Nodes[0]->adjoint() += m_Adjoint * m_Nodes[1]->result();
    m_Nodes[1]->adjoint() += m_Adjoint * m_Nodes[0]->result();
  }
} } }
