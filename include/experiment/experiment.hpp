#include <memory>
#include <string>
#include <vector>

namespace orca
{
  namespace experiment
  {
    class Node;
    using node_ptr_t = std::shared_ptr<Node>;
    using node_ptr_coll_t = std::vector<node_ptr_t>;

    class Node
    {
    public:
      virtual ~Node(void) = default;
    public:
      virtual double getValue(void) const;
      virtual void setValue(double value);
      virtual double calculate(void) const = 0;
    protected:
      node_ptr_coll_t m_Arguments;
    };

    class Number
    {
    public:
      Number(double value);
      Number(const node_ptr_t& node);
    public:
      const node_ptr_t& node(void) const;
      double getValue(void) const;
      void setValue(double value);
      double calculate(void) const;
    private:
      node_ptr_t m_Node;
    };

    node_ptr_t operator+(const Number& lhs, const Number& rhs);
    node_ptr_t operator*(const Number& lhs, const Number& rhs);
    node_ptr_t log(const Number& arg);
  }
}
