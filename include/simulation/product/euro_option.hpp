#pragma once

#include "simulation/simulation.hpp"
#include "simulation/product.hpp"
#include "simulation/sample_def.hpp"
#include "simulation/sample.hpp"
#include "math/util.hpp"

namespace orca { namespace simulation { namespace product {
  template<typename T>
  class EuropeanOption : public Product<T>
  {
  public:
    EuropeanOption(dbl_t strike,
                   dbl_t expiry,
                   dbl_t settlement) :
      m_Strike(strike),
      m_Expiry(expiry),
      m_Settlement(settlement),
      m_Labels(1U)
    {
      // Timeline: only the expiry date
      m_Timeline.push_back(m_Expiry);

      // Defline: only one sample on the expiry date
      m_Defline.resize(1U);
      m_Defline[0].m_Numeraire = true;
      m_Defline[0].m_ForwardMaturities.push_back(settlement);
      m_Defline[0].m_DiscountMaturities.push_back(settlement);

      std::ostringstream oss;
      oss.precision(2);
      oss << std::fixed;
      if (math::util::areEqualToMachineTolerance(expiry, settlement))
        oss << "call " << m_Strike << " " << m_Expiry;
      else
        oss << "call " << m_Strike << " " << m_Expiry << " " << m_Settlement;

      m_Labels[0] = oss.str();
    }
    EuropeanOption(dbl_t strike,
                   dbl_t expiry) :
      EuropeanOption(strike, expiry, expiry)
    { }
  public:
    virtual const time_vec_t& timeline(void) const override
    {
      return m_Timeline;
    }
    virtual const sample_def_vec_t& defline(void) const override
    {
      return m_Defline;
    }
    virtual const string_vec_t& payoffLabels(void) const override
    {
      return m_Labels;
    }
    virtual product_ptr_t<T> clone(void) const override
    {
      return std::make_unique<EuropeanOption<T>>(*this);
    }
    virtual void payoffs(const scenario_t<T>& path,
                         std::vector<T>& payoffs) const override
    {
      payoffs[0] = std::max(path[0].m_Forwards[0] - m_Strike, 0.)
                 * path[0].m_Discounts[0] / path[0].m_Numeraire;
    }
  private:
    dbl_t m_Strike;
    dbl_t m_Expiry;
    dbl_t m_Settlement;

    dbl_vec_t m_Timeline;
    sample_def_vec_t m_Defline;
    string_vec_t m_Labels;
  };
}}}
