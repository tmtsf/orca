#pragma once

#include "simulation/simulation.hpp"
#include "simulation/sample_def.hpp"

namespace orca { namespace simulation {
  // A sample is a collection of market observations on an event date for the evaluation
  // of the payoff. Currently, it only supports single underlying
  template<typename T>
  struct Sample
  {
    T              m_Numeraire;
    std::vector<T> m_Forwards;
    std::vector<T> m_Discounts;
    std::vector<T> m_Libors;

    void allocate(const SampleDef& data)
    {
      m_Forwards.resize(data.m_ForwardMaturities.size());
      m_Discounts.resize(data.m_DiscountMaturities.size());
      m_Libors.resize(data.m_LiborDefs.size());
    }

    void initialize(void)
    {
      m_Numeraire = T(1.);
      std::fill(m_Forwards.begin(), m_Forwards.end(), T(100.));
      std::fill(m_Discounts.begin(), m_Discounts.end(), T(1.));
      std::fill(m_Libors.begin(), m_Libors.end(), T(0.));
    }
  };
}}
