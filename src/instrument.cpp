//
// Created by lukla on 17.06.2022.
//

#include "instrument.hpp"

arma::dvec AdditiveSynth::operator()(const Note& note, const Temperament& tmp, double bpm, const TrackData& data) const
{
    arma::dvec res(note.duration_ * 60 * data.sampleRate / bpm, arma::fill::zeros);
    arma::dvec temp(note.duration_ * 60 * data.sampleRate / bpm, arma::fill::zeros);
    double amplitude = 0.0;

    //generate waveform
    for(auto& [osc, fr, amp] : osc_)
    {
        //std::cout << typeid(osc).name() << '\n';
        osc.setFrequency(fr * tmp(note));
        osc.setAmplitude(amp * note.volume_);
        Sampler sampler(data.sampleRate, osc);
        temp.imbue(sampler);
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