//
// Created by lukla on 18.06.2022.
//

#ifndef POZAKRES_FILTER_HPP
#define POZAKRES_FILTER_HPP

class LowPassFilter
{
    double sampleRate_;
    double frequency_;
    double prev_;

public:
    LowPassFilter(double sampleRate_, double frequency_) : sampleRate_(sampleRate_), frequency_(frequency_), prev_(0.0) {}
    [[nodiscard]] double getFrequency() const
    {
        return frequency_;
    }
    void setFrequency(double f)
    {
        frequency_ = f;
    }
    double operator()(double in_);
};

#endif //POZAKRES_FILTER_HPP
