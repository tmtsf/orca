#pragma once

#include "simulation/sample.hpp"
#include "math/util.hpp"

namespace orca { namespace simulation { namespace model {
  template<typename T>
  class BlackScholesModel : public Model<T>
  {
  public:
    template<typename U>
    BlackScholesModel(const U& spot,
                      const U& vol,
                      bool isSpotMeasure = false,
                      const U& discountRate = U(0.),
                      const U& dividendYield = U(0.)) :
      m_Spot(spot),
      m_Vol(vol),
      m_IsSpotMeasure(isSpotMeasure),
      m_DiscountRate(discountRate),
      m_DividendYield(dividendYield),
      m_Parameters(4U),
      m_ParameterLabels({"spot", "vol", "rate", "div"})
    {
      setParameterPointers();
    }
  public:
    T spot(void) const
    {
      return m_Spot;
    }
    T volatility(void) const
    {
      return m_Vol;
    }
    T discountRate(void) const
    {
      return m_DiscountRate;
    }
    T dividendYield(void) const
    {
      return m_DividendYield;
    }
    virtual const std::vector<T*>& parameters(void) override
    {
      return m_Parameters;
    }
    virtual const string_vec_t& parameterLabels(void) const override
    {
      return m_ParameterLabels;
    }
    virtual model_ptr_t<T> clone(void) const override
    {
      auto m = std::make_unique<BlackScholesModel<T>>(*this);
      m->setParameterPointers();
      return m;
    }
    void allocate(const time_vec_t& productTimeline,
                  const sample_def_vec_t& defline) override
    {
      m_Timeline.clear();
      m_Timeline.push_back(0.);
      for (const auto& time : productTimeline)
      {
        if (math::util::isPositive(time))
          m_Timeline.push_back(time);
      }

      m_TodayOnTimeline = math::util::areEqualToMachineTolerance(productTimeline[0], 0.);
      m_Defline = &defline;

      m_StandardDeviations.resize(m_Timeline.size() - 1);
      m_Drifts.resize(m_Timeline.size() - 1);

      size_t n = productTimeline.size();
      m_Numeraires.resize(n);

      m_DiscountFactors.resize(n);
      for (size_t j = 0; j < n; ++j)
        m_DiscountFactors[j].resize(defline[j].m_DiscountMaturities.size());

      m_ForwardFactors.resize(n);
      for (size_t j = 0; j < n; ++j)
        m_ForwardFactors[j].resize(defline[j].m_ForwardMaturities.size());

      m_Libors.resize(n);
      for (size_t j = 0; j < n; ++j)
        m_Libors[j].resize(defline[j].m_LiborDefs.size());
    }
    virtual void init(const time_vec_t& productTimeline,
                      const sample_def_vec_t& defline) override
    {
      T drift = m_DiscountRate - m_DividendYield;
      size_t n = m_Timeline.size() - 1;
      for (size_t i = 0; i < n; ++i)
      {
        dbl_t dt = m_Timeline[i + 1] - m_Timeline[i];
        m_StandardDeviations[i] = m_Vol * std::sqrt(dt);

        if (m_IsSpotMeasure)
          m_Drifts[i] = (drift + .5 * m_Vol * m_Vol) * dt;
        else
          m_Drifts[i] = (drift - .5 * m_Vol * m_Vol) * dt;
      }

      size_t m = productTimeline.size();
      for (size_t i = 0; i < m; ++i)
      {
        if (defline[i].m_Numeraire)
        {
          if (m_IsSpotMeasure)
            m_Numeraires[i] = exp(m_DividendYield * productTimeline[i]) / m_Spot;
          else
            m_Numeraires[i] = exp(m_DiscountRate * productTimeline[i]);
        }

        size_t nFF = defline[i].m_ForwardMaturities.size();
        for (size_t j = 0; j < nFF; ++j)
        {
          m_ForwardFactors[i][j] = exp(drift * (defline[i].m_ForwardMaturities[j]
                                                      - productTimeline[i]));
        }

        size_t nDF = defline[i].m_DiscountMaturities.size();
        for (size_t j = 0; j < nDF; ++j)
        {
          m_DiscountFactors[i][j] = exp(-m_DiscountRate * (defline[i].m_DiscountMaturities[j]
                                                            - productTimeline[i]));
        }

        size_t nL = defline[i].m_LiborDefs.size();
        for (size_t j = 0; j < nL; ++j)
        {
          dbl_t dt = defline[i].m_LiborDefs[j].m_End - defline[i].m_LiborDefs[j].m_Start;
          m_Libors[i][j] = (exp(m_DiscountRate * dt) - 1.) / dt;
        }
      }
    }
    virtual size_t simDimension(void) const override
    {
      return m_Timeline.size() - 1;
    }
    virtual void generatePath(const dbl_vec_t& gaussianVector,
                              scenario_t<T>& path) const override
    {
      T spot = m_Spot;
      size_t index = 0;
      if (m_TodayOnTimeline)
      {
        fillScenario(index, spot, path[index], (*m_Defline)[index]);
        ++index;
      }

      size_t n = m_Timeline.size() - 1;
      for (size_t i = 0; i < n; ++i)
      {
        spot = spot * exp(m_Drifts[i] + m_StandardDeviations[i] * gaussianVector[i]);
        fillScenario(index, spot, path[index], (*m_Defline)[index]);
        ++index;
      }
    }
  private:
    void setParameterPointers(void)
    {
      m_Parameters = {&m_Spot, &m_Vol, &m_DiscountRate, &m_DividendYield};
    }
    void fillScenario(size_t index,
                      const T& spot,
                      Sample<T>& scenario,
                      const SampleDef& def) const
    {
      if (def.m_Numeraire)
      {
        scenario.m_Numeraire = m_Numeraires[index];
        if (m_IsSpotMeasure)
          scenario.m_Numeraire *= spot;
      }

      std::transform(m_ForwardFactors[index].begin(),
                     m_ForwardFactors[index].end(),
                     scenario.m_Forwards.begin(),
                     [&spot](const T& ff)
                     { return spot * ff; });

      std::copy(m_DiscountFactors[index].begin(),
                m_DiscountFactors[index].end(),
                scenario.m_Discounts.begin());

      std::copy(m_Libors[index].begin(),
                m_Libors[index].end(),
                scenario.m_Libors.begin());
    }
  private:
    T m_Spot;
    T m_DiscountRate;
    T m_DividendYield;
    T m_Vol;
    bool m_IsSpotMeasure;

    time_vec_t m_Timeline;
    bool m_TodayOnTimeline;

    const sample_def_vec_t* m_Defline;

    std::vector<T> m_StandardDeviations;
    std::vector<T> m_Drifts;

    std::vector<std::vector<T>> m_ForwardFactors;

    std::vector<T> m_Numeraires;
    std::vector<std::vector<T>> m_DiscountFactors;
    std::vector<std::vector<T>> m_Libors;

    std::vector<T*> m_Parameters;
    string_vec_t m_ParameterLabels;
  };
}}}
