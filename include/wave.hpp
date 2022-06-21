//
// Created by lukla on 16.06.2022.
//

#ifndef POZAKRES_WAVE_HPP
#define POZAKRES_WAVE_HPP

#include <cmath>
#include <numbers>

class Sine
{
    double frequency_;
    double phase_;
    double amplitude_;

public:
    Sine() : frequency_(0.0), phase_(0.0), amplitude_(0.0) {}
    Sine(double f, double p, double a) : frequency_(f), phase_(p), amplitude_(a) {}
    [[nodiscard]] double getFrequency() const
    {
       return frequency_;
    }
    [[nodiscard]] double getPhase() const
    {
        return phase_;
    }
    [[nodiscard]] double getAmplitude() const
    {
        return amplitude_;
    }
    void setFrequency(double f)
    {
        frequency_ = f;
    }
    void setPhase(double p)
    {
        phase_ = p;
    }
    void setAmplitude(double a)
    {
        amplitude_ = a;
    }
    double operator()(double arg) const
    {
        return amplitude_ * std::sin(2.0 * std::numbers::pi * frequency_ * arg + phase_);
    }
};

class Square
{
    double frequency_;
    double phase_;
    double amplitude_;

public:
    Square() : frequency_(0.0), phase_(0.0), amplitude_(0.0) {}
    Square(double f, double p, double a) : frequency_(f), phase_(p), amplitude_(a) {}
    [[nodiscard]] double getFrequency() const
    {
        return frequency_;
    }
    [[nodiscard]] double getPhase() const
    {
        return phase_;
    }
    [[nodiscard]] double getAmplitude() const
    {
        return amplitude_;
    }
    void setFrequency(double f)
    {
        frequency_ = f;
    }
    void setPhase(double p)
    {
        phase_ = p;
    }
    void setAmplitude(double a)
    {
        amplitude_ = a;
    }
    double operator()(double arg) const
    {
        double ph = frequency_ * arg + phase_;
        return 2.0 * amplitude_ * (2.0 * std::floor(ph) - std::floor(2.0 * ph)) + amplitude_;
    }
};

class Sawtooth
{
    double frequency_;
    double phase_;
    double amplitude_;

public:
    Sawtooth() : frequency_(0.0), phase_(0.0), amplitude_(0.0) {}
    Sawtooth(double f, double p, double a) : frequency_(f), phase_(p), amplitude_(a) {}
    [[nodiscard]] double getFrequency() const
    {
        return frequency_;
    }
    [[nodiscard]] double getPhase() const
    {
        return phase_;
    }
    [[nodiscard]] double getAmplitude() const
    {
        return amplitude_;
    }
    void setFrequency(double f)
    {
        frequency_ = f;
    }
    void setPhase(double p)
    {
        phase_ = p;
    }
    void setAmplitude(double a)
    {
        amplitude_ = a;
    }
    double operator()(double arg) const
    {
        double ph = arg * frequency_ + phase_;
        return 2.0 * amplitude_ * (ph - std::floor(0.5 + ph));
    }
};

class Triangle
{
    double frequency_;
    double phase_;
    double amplitude_;

public:
    Triangle() : frequency_(0.0), phase_(0.0), amplitude_(0.0) {}
    Triangle(double f, double p, double a) : frequency_(f), phase_(p), amplitude_(a) {}
    [[nodiscard]] double getFrequency() const
    {
        return frequency_;
    }
    [[nodiscard]] double getPhase() const
    {
        return phase_;
    }
    [[nodiscard]] double getAmplitude() const
    {
        return amplitude_;
    }
    void setFrequency(double f)
    {
        frequency_ = f;
    }
    void setPhase(double p)
    {
        phase_ = p;
    }
    void setAmplitude(double a)
    {
        amplitude_ = a;
    }
    double operator()(double arg) const
    {
        double ph = frequency_ * arg + phase_;
        return 4.0 * amplitude_ * std::abs(ph - std::floor(0.5 + ph)) - amplitude_;
    }
};

#endif //POZAKRES_WAVE_HPP
