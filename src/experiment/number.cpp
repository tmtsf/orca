#include "experiment/number.hpp"
#include "experiment/node.hpp"
#include "experiment/visitors/evaluatoin.hpp"

namespace orca
{
  namespace experiment
  {
    Number::Number(double value) :
      m_Node(makeLeafNode(value))
    {}

    Number::Number(const node_ptr_t& node) :
      m_Node(node)
    {}

    const node_ptr_t& Number::node(void) const
    {
      return m_Node;
    }

    double Number::getValue(void) const
    {
      return m_Node->getValue();
    }

    void Number::setValue(double value)
    {
      m_Node->setValue(value);
    }

    double Number::calculate(void) const
    {
      EvaluationVisitor v;
      return m_Node->accept(v);
    }
  }
}
