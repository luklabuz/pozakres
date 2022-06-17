//
// Created by lukla on 16.06.2022.
//

#ifndef POZAKRES_NOISE_HPP
#define POZAKRES_NOISE_HPP

#include <random>
#include "random.hpp"

class WhiteNoise
{
    double amplitude_;

public:
    WhiteNoise() : amplitude_(1.0) {}
    explicit WhiteNoise(double a) : amplitude_(a) {}
    void setFrequency(double f) {}
    void setPhase(double p) {}
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
