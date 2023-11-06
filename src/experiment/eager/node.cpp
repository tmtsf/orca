#include "experiment/eager/nodes/summation.hpp"
#include "experiment/eager/nodes/multiplication.hpp"
#include "experiment/eager/nodes/logarithm.hpp"
#include "experiment/eager/nodes/leaf.hpp"
#include "experiment/eager/number.hpp"

namespace orca { namespace experiment { namespace eager {
    Node::Node(const node_ptr_coll_t& nodes) :
      m_Nodes(nodes)
    {
      ++m_Count;
      m_ID = m_Count;
    }

    const node_ptr_coll_t& Node::children(void) const
    {
      return m_Nodes;
    }

    size_t Node::m_Count = 0;

    size_t Node::id(void) const
    {
      return m_ID;
    }

    dbl_t Node::getValue(void) const
    {
      throw("getValue() is not implemented");
      return 0.;
    }

    void Node::setValue(dbl_t value)
    {
      throw("setValue() is not implemented");
    }

    node_ptr_t makeLeafNode(dbl_t value)
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
} } }
