#include "experiment/eager/nodes/summation.hpp"
#include "experiment/eager/nodes/multiplication.hpp"
#include "experiment/eager/nodes/logarithm.hpp"
#include "experiment/eager/nodes/leaf.hpp"
#include "experiment/eager/number.hpp"

namespace orca { namespace experiment { namespace eager {
  Node::Node(const node_ptr_coll_t& nodes) :
    m_Nodes(nodes),
    m_Result(0.),
    m_Adjoint(0.)
  { }

  dbl_t Node::getValue(void) const
  {
    throw("getValue() is not implemented");
    return 0.;
  }

  void Node::setValue(dbl_t value)
  {
    throw("setValue() is not implemented");
  }

  value_t Node::result(void) const
  {
    return m_Result;
  }

  adjoint_t& Node::adjoint(void)
  {
    return m_Adjoint;
  }

  void Node::resetAdjoints(void)
  {
    for (auto n : m_Nodes)
      n->resetAdjoints();

    m_Adjoint = 0.;
  }

  node_ptr_t makeLeafNode(dbl_t value)
  {
    return new Leaf(value);
  }

  Number operator+(const Number& lhs, const Number& rhs)
  {
    node_ptr_t n = new Summation(lhs.node(), rhs.node());
    Number::m_Tape.emplace_back(n);
    return n;
  }

  Number operator*(const Number& lhs, const Number& rhs)
  {
    node_ptr_t n = new Multiplication(lhs.node(), rhs.node());
    Number::m_Tape.emplace_back(n);
    return n;
  }

  Number log(const Number& arg)
  {
    node_ptr_t n = new Logarithm(arg.node());
    Number::m_Tape.emplace_back(n);
    return n;
  }
} } }
