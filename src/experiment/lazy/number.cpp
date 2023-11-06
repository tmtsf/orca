#include "experiment/lazy/number.hpp"
#include "experiment/lazy/node.hpp"
#include "experiment/lazy/visitors/evaluation.hpp"
#include "experiment/lazy/visitors/log.hpp"
#include "experiment/lazy/visitors/adjoint.hpp"

namespace orca { namespace experiment { namespace lazy {
    Number::Number(dbl_t value) :
      m_Node(makeLeafNode(value))
    {}

    Number::Number(const node_ptr_t& node) :
      m_Node(node)
    {}

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

    dbl_t Number::calculate(void) const
    {
      EvaluationVisitor v;
      m_Node->accept(v);
      m_Values = v.values();
      return v.getResult();
    }

    void Number::printLog(void) const
    {
      LogVisitor v;
      m_Node->accept(v);
    }

    const adjoint_map_t& Number::adjoints(void) const
    {
      AdjointVisitor v(m_Values);
      m_Node->accept(v);
      m_Adjoints = v.ajoints();
      return m_Adjoints;
    }
} } }
