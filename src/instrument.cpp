//
// Created by lukla on 17.06.2022.
//

#include "instrument.hpp"

arma::dvec AdditiveSynth::operator()(const Note& note, const Temperament& tmp, double bpm, const TrackData& data)
{
    arma::dvec res(note.duration_ * 60 * data.sampleRate / bpm, arma::fill::zeros);
    arma::dvec temp(note.duration_ * 60 * data.sampleRate / bpm, arma::fill::zeros);
    double amplitude = 0.0;

    //generate waveform
    for(auto& [osc, fr, amp] : osc_)
    {
        if(note.value_ == "")
            temp.fill(0.0);
        else
        {
            osc.setFrequency(fr * tmp(note));
            osc.setAmplitude(amp * note.volume_);
            Sampler sampler(data.sampleRate, osc);
            temp.imbue(sampler);
        }
        res += temp;
        amplitude += amp;
    }
    res /= amplitude;

    //apply envelope
    //attack
    arma::dvec attack = arma::linspace(0.0, 1.0, adsr_.attack_ * data.sampleRate);
    res.subvec(0, adsr_.attack_ * data.sampleRate - 1) %= attack;

    //decay
    arma::dvec decay = arma::linspace(1.0, adsr_.sustain_, adsr_.decay_ * data.sampleRate);
    res.subvec(adsr_.attack_ * data.sampleRate, (adsr_.attack_ + adsr_.decay_) * data.sampleRate - 1) %= decay;

    //sustain
    res.subvec((adsr_.attack_ + adsr_.decay_) * data.sampleRate, res.size() - adsr_.release_ * data.sampleRate - 1) *= adsr_.sustain_;

    //release
    arma::dvec release = arma::linspace(adsr_.sustain_, 0.0, adsr_.release_ * data.sampleRate);
    res.subvec(res.size() - adsr_.release_ * data.sampleRate, res.size() - 1) %= release;

    return res;
}

arma::dvec FilteredNoise::operator()(const Note& note, const Temperament&, double bpm, const TrackData& data)
{
    arma::dvec res(note.duration_ * 60 * data.sampleRate / bpm, arma::fill::zeros);
    noise_.setAmplitude(note.volume_);
    Sampler sampler(data.sampleRate, noise_);
    Sampler lfo(data.sampleRate, lfo_);

    double freq = filter_.getFrequency();

    res.imbue(sampler);
    res.transform([=, this, &lfo](double x) {
        double f = lfo();
        filter_.setFrequency(freq + f);
        return filter_(x);
    });

    return res;
}
