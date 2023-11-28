#pragma once

#include "simulation/simulation.hpp"

namespace orca { namespace simulation {
  struct SampleDef
  {
    // numeraire is needed for a payment date
    bool                 m_Numeraire;
    time_vec_t           m_ForwardMaturities;
    time_vec_t           m_DiscountMaturities;

    struct RateDef
    {
      time_t      m_Start;
      time_t      m_End;
      std::string m_Curve;

      RateDef(const time_t& start,
              const time_t& end,
              const std::string& curve) :
        m_Start(start),
        m_End(end),
        m_Curve(curve)
      { }
    };

    std::vector<RateDef> m_LiborDefs;

    SampleDef(void) :
      m_Numeraire(true)
    { }
  };
}}
