#include "experiment/eager/visitors/log.hpp"

#include <iostream>

namespace orca { namespace experiment { namespace eager {
    void LogVisitor::visit(const Summation& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
        return;

      m_Visited[id] = true;
      n.children()[0]->accept(*this);
      n.children()[1]->accept(*this);
      std::cout << "y" << n.id()
                << " = y" << n.children()[0]->id()
                << " + y" << n.children()[1]->id()
                << std::endl;
    }

    void LogVisitor::visit(const Multiplication& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
        return;

      m_Visited[id] = true;
      n.children()[0]->accept(*this);
      n.children()[1]->accept(*this);
      std::cout << "y" << n.id()
                << " = y" << n.children()[0]->id()
                << " * y" << n.children()[1]->id()
                << std::endl;
    }

    void LogVisitor::visit(const Logarithm& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
        return;

      m_Visited[id] = true;
      n.children()[0]->accept(*this);
      std::cout << "y" << n.id()
                << " = log(y" << n.children()[0]->id()
                << ")" << std::endl;
    }

    void LogVisitor::visit(const Leaf& n)
    {
      size_t id = n.id();
      if (m_Visited.count(id))
        return;

      m_Visited[id] = true;
      std::cout << "y" << n.id()
                << " = " << n.getValue()
                << std::endl;
    }
} } }
