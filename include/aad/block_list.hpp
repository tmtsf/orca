#pragma once

#include "aad/aad.hpp"

namespace orca { namespace aad {
  template<typename T, size_t BlockSize>
  class BlockList
  {
  public:
    using list_iter_t = typename array_list_t<T, BlockSize>::iterator;
    using block_iter_t = typename array_t<T, BlockSize>::iterator;

    BlockList(void)
    {
      newBlock();
    }
    void clear(void)
    {
      m_Data.clear();
      newBlock();
    }
    void rewind(void)
    {
      m_CurrBlock = m_Data.begin();
      m_NextSpace = m_CurrBlock->begin();
      m_LastSpace = m_CurrBlock->end();
    }
    void setMark(void)
    {
      m_MarkedBlock = m_CurrBlock;
      m_MarkedSpace = m_NextSpace;
    }
    void rewindToMark(void)
    {
      m_CurrBlock = m_MarkedBlock;
      m_NextSpace = m_MarkedSpace;
      m_LastSpace = m_CurrBlock->end();
    }
    T* emplace_back(void)
    {
      if (m_NextSpace == m_LastSpace)
      {
        nextBlock();
      }

      auto temp = m_NextSpace;
      ++m_NextSpace;
      return &*temp;
    }
    template<size_t n>
    T* emplace_back_multi(void)
    {
      if (std::distance(m_NextSpace, m_LastSpace) < n)
      {
        nextBlock();
      }

      auto temp = m_NextSpace;
      m_NextSpace += n;
      return &*temp;
    }
    T* emplace_back_multi(size_t n)
    {
      if (std::distance(m_NextSpace, m_LastSpace) < n)
      {
        nextBlock();
      }

      auto temp = m_NextSpace;
      m_NextSpace += n;
      return &*temp;
    }
    void memset(unsigned char value = 0)
    {
      for (auto& arr : m_Data)
      {
        std::memset(&arr[0], value, BlockSize * sizeof(T));
      }
    }
    template<typename ...Args>
    T* emplace_back(Args&& ...args)
    {
      if (m_NextSpace == m_LastSpace)
      {
        nextBlock();
      }

      T* emplaced = new (&*m_NextSpace) T(std::forward<Args>(args)...);
      ++m_NextSpace;
      return emplaced;
    }

    class iterator
    {
    public:
      using difference_type = ptrdiff_t;
      using reference = T&;
      using pointer = T*;
      using value_type = T;
      using iterator_category = std::bidirectional_iterator_tag;
    public:
      iterator(void) = default;
      iterator(list_iter_t currBlock,
               block_iter_t currSpace,
               block_iter_t firstSpace,
               block_iter_t lastSpace) :
        m_IterCurrBlock(currBlock),
        m_IterCurrSpace(currSpace),
        m_IterFirstSpace(firstSpace),
        m_IterLastSpace(lastSpace)
      { }
      iterator& operator++(void)
      {
        ++m_IterCurrSpace;

        if (m_IterCurrSpace == m_IterLastSpace)
        {
          ++m_IterCurrBlock;
          m_IterFirstSpace = m_IterCurrBlock->begin();
          m_IterLastSpace = m_IterCurrBlock->end();
          m_IterCurrSpace = m_IterFirstSpace;
        }

        return *this;
      }
      iterator& operator--(void)
      {
        if (m_IterCurrSpace == m_IterFirstSpace)
        {
          --m_IterCurrBlock;
          m_IterFirstSpace = m_IterCurrBlock->begin();
          m_IterLastSpace = m_IterCurrBlock->end();
          m_IterCurrSpace = m_IterLastSpace;
        }

        --m_IterCurrSpace;
        return *this;
      }
      T& operator*(void)
      {
        return *m_IterCurrSpace;
      }
      const T& operator*(void) const
      {
        return *m_IterCurrSpace;
      }
      T* operator->(void)
      {
        return &*m_IterCurrSpace;
      }
      const T* operator->(void) const
      {
        return &*m_IterCurrSpace;
      }
      bool operator==(const iterator& rhs) const
      {
        return (m_IterCurrBlock == rhs.m_IterCurrBlock && m_IterCurrSpace == rhs.m_IterCurrSpace);
      }
      bool operator!=(const iterator& rhs) const
      {
        return (m_IterCurrBlock != rhs.m_IterCurrBlock || m_IterCurrSpace != rhs.m_IterCurrSpace);
      }
    private:
      list_iter_t m_IterCurrBlock;
      block_iter_t m_IterCurrSpace;
      block_iter_t m_IterFirstSpace;
      block_iter_t m_IterLastSpace;
    };
  public:
    iterator begin(void)
    {
      return iterator(m_Data.begin(),
                      m_Data.begin()->begin(),
                      m_Data.begin()->begin(),
                      m_Data.begin()->end());
    }
    iterator end(void)
    {
      return iterator(m_CurrBlock,
                      m_NextSpace,
                      m_CurrBlock->begin(),
                      m_CurrBlock->end());
    }
    iterator mark(void)
    {
      return iterator(m_MarkedBlock,
                      m_MarkedSpace,
                      m_MarkedBlock->begin(),
                      m_MarkedBlock->end());
    }
    iterator find(const T* const element)
    {
      iterator it = end();
      iterator b = begin();

      while (it != b)
      {
        --it;
        if (&*it == element)
          return it;
      }

      if (&*it == element)
          return it;

      return end();
    }
  private:
    void newBlock(void)
    {
      m_Data.emplace_back();

      m_CurrBlock = std::prev(m_Data.end());
      m_LastBlock = m_CurrBlock;
      m_NextSpace = m_CurrBlock->begin();
      m_LastSpace = m_CurrBlock->end();
    }
    void nextBlock(void)
    {
      if (m_CurrBlock == m_LastBlock)
      {
        newBlock();
      }
      else
      {
        ++m_CurrBlock;
        m_NextSpace = m_CurrBlock->begin();
        m_LastSpace = m_CurrBlock->end();
      }
    }

  private:
    array_list_t<T, BlockSize> m_Data;

    list_iter_t      m_CurrBlock;         // current block
    list_iter_t      m_LastBlock;         // last block

    block_iter_t     m_NextSpace;         // next free space in current block
    block_iter_t     m_LastSpace;         // end of the current block

    list_iter_t      m_MarkedBlock;       // marked block
    block_iter_t     m_MarkedSpace;       // marked space
  };
}}
