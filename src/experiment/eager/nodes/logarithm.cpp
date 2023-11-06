#include "experiment/eager/nodes/logarithm.hpp"
#include "experiment/eager/node.hpp"
#include "experiment/eager/visitor.hpp"

namespace orca { namespace experiment { namespace eager {
    Logarithm::Logarithm(const node_ptr_t& arg) :
        Node({arg})
    { }

    void Logarithm::accept(Visitor& v) const
    {
      return v.visit(*this);
    }
} } }
