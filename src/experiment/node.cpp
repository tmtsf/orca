#include "experiment/nodes/summation.hpp"
#include "experiment/nodes/multiplication.hpp"
#include "experiment/nodes/logarithm.hpp"
#include "experiment/nodes/leaf.hpp"
#include "experiment/number.hpp"

namespace orca
{
  namespace experiment
  {
    Node::Node(const node_ptr_coll_t& nodes) :
      m_Nodes(nodes)
    {}

    const node_ptr_coll_t& Node::children(void) const
    {
      return m_Nodes;
    }
    double Node::getValue(void) const
    {
      throw("getValue() is not implemented");
      return 0.;
    }

    void Node::setValue(double value)
    {
      throw("setValue() is not implemented");
    }

    template<typename R>
    R Node::accept(const Visitor<R>& v)
    {
      return v.visit(*this);
    }

    node_ptr_t makeLeafNode(double value)
    {
      return std::make_shared<Leaf>(value);
    }

    node_ptr_t operator+(const Number& lhs, const Number& rhs)
    {
      return std::make_shared<Summation>(lhs.node(), rhs.node());
    }

    node_ptr_t operator*(const Number& lhs, const Number& rhs)
    {
      return std::make_shared<Multiplication>(lhs.node(), rhs.node());
    }

    node_ptr_t log(const Number& arg)
    {
      return std::make_shared<Logarithm>(arg.node());
    }
  }
}
