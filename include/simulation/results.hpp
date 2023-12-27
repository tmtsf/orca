#pragma once

#include "simulation/simulation.hpp"
#include "aad/number.hpp"

namespace orca { namespace simulation {
  struct SimulationResults
  {
    SimulationResults(size_t numPaths,
                      size_t numPayments,
                      size_t numParams) :
      m_Payoffs(numPaths, dbl_vec_t(numPayments)),
      m_Aggregated(numPaths),
      m_Risks(numParams)
    {
    }

    dbl_vec_vec_t m_Payoffs;
    dbl_vec_t m_Aggregated;
    dbl_vec_t m_Risks;
  };

}}
