#pragma once

#include "aad/node.hpp"
#include "aad/tape.hpp"
#include "math/util.hpp"
#include "numeric/gaussian.hpp"

namespace orca { namespace aad {
  class Number
  {
  public:
    Number(void) = default;
    explicit Number(value_t val) :
      m_Value(val)
    {
      createNode<0>();
    }
    Number& operator=(value_t val)
    {
      m_Value = val;
      createNode<0>();

      return *this;
    }
    void putOnTape(void)
    {
      createNode<0>();
    }
    explicit operator value_t&(void)
    {
      return m_Value;
    }
    explicit operator value_t(void) const
    {
      return m_Value;
    }
  public:
    void resetAdjoints(void)
    {
      m_Tape->resetAdjoints();
    }
    static void propagateAdjoints(Tape::iterator from,
                                  Tape::iterator to)
    {
      auto it = from;
      while (it != to)
      {
        it->propagateOne();
        --it;
      }

      it->propagateOne();
    }
    static void propagateMarkToStart(void)
    {
      propagateAdjoints(std::prev(m_Tape->marked()),
                        m_Tape->begin());
    }
    void propagateAdjoints(Tape::iterator to)
    {
      adjoint() = 1.;
      auto from = m_Tape->find(m_Node);
      propagateAdjoints(from, to);
    }
    void propagateToStart(void)
    {
      propagateAdjoints(m_Tape->begin());
    }
    void propagateToMark(void)
    {
      propagateAdjoints(m_Tape->marked());
    }
  public:
    value_t& value(void)
    {
      return m_Value;
    }
    value_t value(void) const
    {
      return m_Value;
    }
    adjoint_t& adjoint(void)
    {
      return m_Node->adjoint();
    }
    adjoint_t adjoint(void) const
    {
      return m_Node->adjoint();
    }
  private:
    // some utility functions
    derivative_t& derivative(void)
    {
      return m_Node->m_DerivativesToChildren[0];
    }
    derivative_t& leftDerivative(void)
    {
      return m_Node->m_DerivativesToChildren[0];
    }
    derivative_t& rightDerivative(void)
    {
      return m_Node->m_DerivativesToChildren[1];
    }
    adjoint_ptr_t& adjointPointer(void)
    {
      return m_Node->m_ChildrenAdjoints[0];
    }
    adjoint_ptr_t& leftAdjointPointer(void)
    {
      return m_Node->m_ChildrenAdjoints[0];
    }
    adjoint_ptr_t& rightAdjointPointer(void)
    {
      return m_Node->m_ChildrenAdjoints[1];
    }
  public:
    static thread_local tape_ptr_t m_Tape;
  private:
    template<size_t N>
    void createNode(void)
    {
      m_Node = m_Tape->recordNode<N>();
    }
    Number(Node& arg, value_t val) :
      m_Value(val)
    {
      createNode<1>();
      m_Node->m_ChildrenAdjoints[0] = &arg.m_SelfAdjoint;
    }
    Number(Node& lhs, Node& rhs, value_t val) :
      m_Value(val)
    {
      createNode<2>();
      m_Node->m_ChildrenAdjoints[0] = &lhs.m_SelfAdjoint;
      m_Node->m_ChildrenAdjoints[1] = &rhs.m_SelfAdjoint;
    }
  public:
    inline friend Number operator*(const Number& lhs, const Number& rhs)
    {
      value_t e = lhs.value() * rhs.value();
      Number result(*lhs.m_Node, *rhs.m_Node, e);
      result.leftDerivative() = rhs.value();
      result.rightDerivative() = lhs.value();

      return result;
    }
    inline friend Number operator*(const Number& lhs, value_t rhs)
    {
      value_t e = lhs.value() * rhs;
      Number result(*lhs.m_Node, e);
      result.derivative() = rhs;

      return result;
    }
    inline friend Number operator*(value_t lhs, const Number& rhs)
    {
      return rhs * lhs;
    }
    inline friend Number operator+(const Number& lhs, const Number& rhs)
    {
      value_t e = lhs.value() + rhs.value();
      Number result(*lhs.m_Node, *rhs.m_Node, e);
      result.leftDerivative() = 1.;
      result.rightDerivative() = 1.;

      return result;
    }
    inline friend Number operator+(const Number& lhs, value_t rhs)
    {
      value_t e = lhs.value() + rhs;
      Number result(*lhs.m_Node, e);
      result.derivative() = 1.;

      return result;
    }
    inline friend Number operator+(value_t lhs, const Number& rhs)
    {
      return rhs + lhs;
    }
    inline friend Number operator/(const Number& lhs, const Number& rhs)
    {
      value_t e = lhs.value() / rhs.value();
      Number result(*lhs.m_Node, *rhs.m_Node, e);
      result.leftDerivative() = 1. / rhs.value();
      result.rightDerivative() = -lhs.value() / rhs.value() / rhs.value();

      return result;
    }
    inline friend Number operator/(const Number& lhs, value_t rhs)
    {
      value_t e = lhs.value() / rhs;
      Number result(*lhs.m_Node, e);
      result.derivative() = 1. / rhs;

      return result;
    }
    inline friend Number operator/(value_t lhs, const Number& rhs)
    {
      value_t e = lhs / rhs.value();
      Number result(*rhs.m_Node, e);
      result.derivative() = -lhs / rhs.value() / rhs.value();

      return result;
    }
    inline friend Number operator-(const Number& lhs, const Number& rhs)
    {
      value_t e = lhs.value() - rhs.value();
      Number result(*lhs.m_Node, *rhs.m_Node, e);
      result.leftDerivative() = 1.;
      result.rightDerivative() = -1.;

      return result;
    }
    inline friend Number operator-(const Number& lhs, value_t rhs)
    {
      value_t e = lhs.value() - rhs;
      Number result(*lhs.m_Node, e);
      result.derivative() = 1.;

      return result;
    }
    inline friend Number operator-(value_t lhs, const Number& rhs)
    {
      value_t e = lhs - rhs.value();
      Number result(*rhs.m_Node, e);
      result.derivative() = -1.;

      return result;
    }
    Number& operator*=(const Number& arg)
    {
      *this = *this * arg;
      return *this;
    }
    Number& operator*=(value_t arg)
    {
      *this = *this * arg;
      return *this;
    }
    Number& operator/=(const Number& arg)
    {
      *this = *this / arg;
      return *this;
    }
    Number& operator/=(value_t arg)
    {
      *this = *this / arg;
      return *this;
    }
    Number& operator+=(const Number& arg)
    {
      *this = *this + arg;
      return *this;
    }
    Number& operator+=(value_t arg)
    {
      *this = *this + arg;
      return *this;
    }
    Number& operator-=(const Number& arg)
    {
      *this = *this - arg;
      return *this;
    }
    Number& operator-=(value_t arg)
    {
      *this = *this - arg;
      return *this;
    }
    Number operator-(void) const
    {
      return 0. - *this;
    }
    Number operator+(void) const
    {
      return *this;
    }
    inline friend Number exp(const Number& arg)
    {
      value_t e = std::exp(arg.value());
      Number result(*arg.m_Node, e);
      result.derivative() = e;

      return result;
    }
    inline friend Number log(const Number& arg)
    {
      value_t e = std::log(arg.value());
      Number result(*arg.m_Node, e);
      result.derivative() = 1. / arg.value();

      return result;
    }
    inline friend Number sqrt(const Number& arg)
    {
      value_t e = std::sqrt(arg.value());
      Number result(*arg.m_Node, e);
      result.derivative() = .5 / e;

      return result;
    }
    inline friend Number fabs(const Number& arg)
    {
      value_t e = std::fabs(arg.value());
      Number result(*arg.m_Node, e);
      result.derivative() = math::util::isPositive(arg.value()) ? 1. : -1.;

      return result;
    }
    inline friend Number normalPDF(const Number& arg)
    {
      value_t e = numeric::normalPDF(arg.value());
      Number result(*arg.m_Node, e);
      result.derivative() = -arg.value() * e;

      return result;
    }
    inline friend Number normalCDF(const Number& arg)
    {
      value_t e = numeric::normalCDF(arg.value());
      Number result(*arg.m_Node, e);
      result.derivative() = numeric::normalPDF(arg.value());

      return result;
    }
    inline friend Number max(const Number& lhs, const Number& rhs)
    {
      value_t e = std::max(lhs.value(), rhs.value());
      Number result(*lhs.m_Node, *rhs.m_Node, e);
      bool leftIsLarger = math::util::isLargerThanMachineTolerance(lhs.value(), rhs.value());
      result.leftDerivative() = leftIsLarger ? 1. : 0.;
      result.rightDerivative() = leftIsLarger ? 0. : 1.;

      return result;
    }
    inline friend Number max(const Number& lhs, value_t rhs)
    {
      value_t e = std::max(lhs.value(), rhs);
      Number result(*lhs.m_Node, e);
      result.derivative() = math::util::isLargerThanMachineTolerance(lhs.value(), rhs) ? 1. : 0.;

      return result;
    }
    inline friend Number max(value_t lhs, const Number& rhs)
    {
      return max(rhs, lhs);
    }
  private:
    value_t m_Value;
    node_ptr_t m_Node;
  };
}}
