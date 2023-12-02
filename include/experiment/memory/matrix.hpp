#pragma once

#include "common/common.hpp"

namespace orca { namespace experiment { namespace memory {
  template<typename T>
  class Matrix
  {
  public:
    Matrix(void) :
      m_Rows(0),
      m_Cols(0)
    { }
    Matrix(size_t rows, size_t cols) :
      m_Rows(rows),
      m_Cols(cols),
      m_Data(rows * cols)
    { }
    size_t rows(void) const
    {
      return m_Rows;
    }
    size_t cols(void) const
    {
      return m_Cols;
    }
    T* operator[](size_t row)
    {
      return &m_Data[row * m_Cols];
    }
    const T* operator[](size_t row) const
    {
      return &m_Data[row * m_Cols];
    }
  private:
    size_t m_Rows;
    size_t m_Cols;

    std::vector<T> m_Data;
  };

  inline void naiveMatrixMultiplication(const Matrix<dbl_t>& a,
                                        const Matrix<dbl_t>& b,
                                        Matrix<dbl_t>& c)
  {
    size_t rows = a.rows();
    size_t cols = b.cols();
    size_t n = a.cols();

    for (size_t i = 0; i < rows; ++i)
    {
      auto ai = a[i];
      auto ci = c[i];

      for (size_t j = 0; j < cols; ++j)
      {
        double res = .0;
        for (size_t k = 0; k < n; ++k)
        {
          res += ai[k] * b[k][j];
        }

        c[i][j] = res;
      }
    }
  }

  inline void smartMatrixMultiplication(const Matrix<dbl_t>& a,
                                        const Matrix<dbl_t>& b,
                                        Matrix<dbl_t>& c)
  {
    size_t rows = a.rows();
    size_t cols = b.cols();
    size_t n = a.cols();

    for (size_t i = 0; i < rows; ++i)
    {
      auto ci = c[i];
      for (size_t j = 0; j < cols; ++j)
      {
        ci[j] = .0;
      }
    }

    #pragma omp parallel for
    for (int i = 0; i < rows; ++i)
    {
      auto ai = a[i];
      auto ci = c[i];

      for (size_t k = 0; k < n; ++k)
      {
        auto bk = b[k];
        auto aik = ai[k];

        // #pragma loop(no_vector)
        for (size_t j = 0; j < cols; ++j)
          ci[j] += aik * bk[j];
      }
    }
  }
}}}
