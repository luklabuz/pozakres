//
// Created by lukla on 18.06.2022.
//

#include "filter.hpp"

double LowPassFilter::operator()(double in_)
{
    double alpha = frequency_ / (sampleRate_ + frequency_);
    double out_ = alpha * in_ + (1 - alpha) * prev_;
    prev_ = out_;
    return out_;
}