//
// Created by lukla on 16.06.2022.
//

#ifndef POZAKRES_OSCILLATOR_HPP
#define POZAKRES_OSCILLATOR_HPP

#include <memory>

class Oscillator
{
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void setFrequency(double) = 0;
        virtual void setPhase(double) = 0;
        virtual void setAmplitude(double) = 0;
        virtual double operator()(double) const = 0;
    };

    template<class T>
    struct Model : Concept
    {
        T data_;
        explicit Model(const T& data_) : data_(data_) {}
        void setFrequency(double f) override
        {
            data_.setFrequency(f);
        }
        void setPhase(double p) override
        {
            data_.setPhase(p);
        }
        void setAmplitude(double a) override
        {
            data_.setAmplitude(a);
        }
        double operator()(double arg) const override
        {
            return data_(arg);
        }
    };

    std::shared_ptr<Concept> concept_;

public:

    Oscillator() : concept_(nullptr) {}

    template<class T>
    Oscillator(const T& data_) : concept_(std::make_shared<Model<T>>(data_)) {}

    void setFrequency(double f)
    {
        concept_->setFrequency(f);
    }
    void setPhase(double p)
    {
        concept_->setPhase(p);
    }
    void setAmplitude(double a)
    {
        concept_->setAmplitude(a);
    }

    double operator()(double arg) const
    {
        if(concept_ == nullptr) return 0.0;
        else return (*concept_)(arg);
    }
};

class Sampler
{
    uint32_t sample_;
    double sampleRate_;
    Oscillator sampled_;

public:
    Sampler(uint32_t sampleRate_, Oscillator osc) : sample_(0),
        sampleRate_(static_cast<double>(sampleRate_)), sampled_(std::move(osc)) {}
    double operator()()
    {
        return sampled_(sample_++ / sampleRate_);
    }
};

#endif //POZAKRES_OSCILLATOR_HPP
