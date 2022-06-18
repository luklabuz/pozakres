//
// Created by lukla on 17.06.2022.
//

#ifndef POZAKRES_INSTRUMENT_HPP
#define POZAKRES_INSTRUMENT_HPP

#include <vector>
#include <armadillo>

#include "melody.hpp"
#include "detail.hpp"
#include "oscillator.hpp"
#include "noise.hpp"
#include "filter.hpp"

struct ADSR
{
    double attack_;
    double decay_;
    double sustain_;
    double release_;
};

class Instrument
{
    struct Concept
    {
        virtual ~Concept() = default;
        virtual arma::dvec operator()(const Note&, const Temperament&, double, const TrackData&) = 0;
    };

    template<class T>
    struct Model : Concept
    {
        T data_;
        Model(const T& data_) : data_(data_) {}
        arma::dvec operator()(const Note& note, const Temperament& tmp, double bpm, const TrackData& data) override
        {
            return data_(note, tmp, bpm, data);
        }
    };

    std::shared_ptr<Concept> concept_;

public:

    Instrument() : concept_(nullptr) {}

    template<class T>
    Instrument(const T& data_) : concept_(std::make_shared<Model<T>>(data_)) {}

    arma::dvec operator()(const Note& note, const Temperament& tmp, double bpm, const TrackData& data)
    {
        if(concept_ == nullptr) return {0};
        else return concept_->operator()(note, tmp, bpm, data);
    }
};

class AdditiveSynth
{
public:
    using Oscillators = std::vector<std::tuple<Oscillator, double, double>>;
private:
    Oscillators osc_;
    ADSR adsr_;

public:
    AdditiveSynth(Oscillators osc_, ADSR adsr_) : osc_(std::move(osc_)), adsr_(adsr_) {}
    arma::dvec operator()(const Note&, const Temperament&, double, const TrackData&);
};

class FilteredNoise
{
    WhiteNoise noise_;
    LowPassFilter filter_;
    Oscillator lfo_;

public:
    FilteredNoise(WhiteNoise noise_, LowPassFilter filter_, Oscillator lfo_)
        : noise_(noise_), filter_(filter_), lfo_(lfo_) {}
    arma::dvec operator()(const Note&, const Temperament&, double, const TrackData&);
};

#endif //POZAKRES_INSTRUMENT_HPP
