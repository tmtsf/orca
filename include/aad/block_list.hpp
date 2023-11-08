#pragma once

#include "aad/aad.hpp"

namespace orca { namespace aad {
  template<typename T, size_t BlockSize>
  class BlockList
  {
  public:
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

    using list_iter_t = decltype(m_Data.begin());
    using block_iter_t = decltype(m_Data.back().begin());

    list_iter      m_CurrBlock;         // current block
    list_iter      m_LastBlock;         // last block

    block_iter     m_NextSpace;         // next free space in current block
    block_iter     m_LastSpace;         // end of the current block

    list_iter      m_MarkedBlock;       // marked block
    block_iter     m_MarkedSpace;       // marked space
  };
}}
