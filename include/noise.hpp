//
// Created by lukla on 16.06.2022.
//

#ifndef POZAKRES_NOISE_HPP
#define POZAKRES_NOISE_HPP

#include <random>
#include "detail.hpp"

class WhiteNoise
{
    double amplitude_;

public:
    WhiteNoise() : amplitude_(1.0) {}
    explicit WhiteNoise(double a) : amplitude_(a) {}
    [[nodiscard]] double getFrequency() const
    {
        return 0.0;
    }
    [[nodiscard]] double getPhase() const
    {
        return 0.0;
    }
    [[nodiscard]] double getAmplitude() const
    {
        return amplitude_;
    }
    void setFrequency(double) {}
    void setPhase(double) {}
    void setAmplitude(double a)
    {
        amplitude_ = a;
    }
    double operator()(double) const
    {
        static std::uniform_real_distribution<double> dist(-amplitude_, amplitude_);
        return dist(random());
    }
};

#endif //POZAKRES_NOISE_HPP
