#pragma once

#include "aad/node.hpp"
#include "aad/block_list.hpp"

namespace orca { namespace aad {
  constexpr size_t BLOCKSIZE = 16384;
  constexpr size_t DATASIZE = 65536;

  class Tape
  {
  public:
    template<size_t N>
    Node* recordNode(void)
    {
      Node* node = m_Nodes.emplace_back(N);
      if constexpr(N)
      {
        node->m_DerivativesToChildren = m_Derivatives.emplace_back_multi<N>();
        node->m_ChildrenAdjoints = m_ChildrenAdjoints.emplace_back_multi<N>();
      }

      return node;
    }
    void resetAdjoints(void)
    {
      for (Node& node : m_Nodes)
        node.adjoint() = 0.;
    }
    void clear(void)
    {
      m_Derivatives.clear();
      m_ChildrenAdjoints.clear();
      m_Nodes.clear();
    }
    void rewind(void)
    {
      m_Derivatives.rewind();
      m_ChildrenAdjoints.rewind();
      m_Nodes.rewind();
    }
    void mark(void)
    {
      m_Derivatives.setMark();
      m_ChildrenAdjoints.setMark();
      m_Nodes.setMark();
    }
    void rewindToMark(void)
    {
      m_Derivatives.rewindToMark();
      m_ChildrenAdjoints.rewindToMark();
      m_Nodes.rewindToMark();
    }

    using iterator = BlockList<Node, BLOCKSIZE>::iterator;
    auto begin(void)
    {
      return m_Nodes.begin();
    }
    auto end(void)
    {
      return m_Nodes.end();
    }
    auto marked(void)
    {
      return m_Nodes.mark();
    }
    auto find(Node* node)
    {
      return m_Nodes.find(node);
    }
  private:
    BlockList<Node, BLOCKSIZE> m_Nodes;
    BlockList<derivative_t, DATASIZE> m_Derivatives;
    BlockList<adjoint_ptr_t, DATASIZE> m_ChildrenAdjoints;

    char m_Padding[64];
  };

}}
