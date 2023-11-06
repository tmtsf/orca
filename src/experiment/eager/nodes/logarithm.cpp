#include "experiment/eager/nodes/logarithm.hpp"
#include "experiment/eager/node.hpp"

namespace orca { namespace experiment { namespace eager {
  Logarithm::Logarithm(const node_ptr_t& arg) :
      Node({arg})
  {
    m_Result = std::log(arg->result());
  }

  void Logarithm::propagateAdjoint(void)
  {
    m_Nodes[0]->adjoint() += m_Adjoint / m_Nodes[0]->result();
  }
} } }
