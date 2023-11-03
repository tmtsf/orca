#include "experiment/experiment.hpp"

#include <cmath>

namespace orca
{
  namespace experiment
  {
    namespace
    {
      class Summation : public Node
      {
      public:
        Summation(const node_ptr_t& lhs, const node_ptr_t& rhs)
        {
          m_Arguments = {lhs, rhs};
        }
        virtual double calculate(void) const override
        {
          return m_Arguments[0]->calculate() + m_Arguments[1]->calculate();
        }
      };

      class Multiplication : public Node
      {
      public:
        Multiplication(const node_ptr_t& lhs, const node_ptr_t& rhs)
        {
          m_Arguments = {lhs, rhs};
        }
        virtual double calculate(void) const override
        {
          return m_Arguments[0]->calculate() * m_Arguments[1]->calculate();
        }
      };

      class Logarithm : public Node
      {
      public:
        Logarithm(const node_ptr_t& arg)
        {
          m_Arguments = {arg};
        }
        virtual double calculate(void) const override
        {
          return std::log(m_Arguments[0]->calculate());
        }
      };

      class Leaf : public Node
      {
      public:
        Leaf(double value) :
          m_Value(value)
        {}
      public:
        virtual double getValue(void) const override
        {
          return m_Value;
        }
        virtual void setValue(double value) override
        {
          m_Value = value;
        }
        virtual double calculate(void) const override
        {
          return m_Value;
        }
      private:
        double m_Value;
      };
    }

    double Node::getValue(void) const
    {
      throw("not implemented");
      return 0.;
    }

    void Node::setValue(double value)
    {
      throw("not implemented");
    }

    Number::Number(double value) :
      m_Node(std::make_shared<Leaf>(value))
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
      return m_Node->calculate();
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
