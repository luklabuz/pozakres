//
// Created by lukla on 17.06.2022.
//

#include <cmath>
#include "melody.hpp"

Temperament& equal_temperament()
{
    static std::unordered_map<std::string, double> lookup_table = {
            {"C", 261.63}, {"C#", 277.18}, {"Db", 277.18}, {"D", 293.66}, {"D#", 311.13}, {"Eb", 311.13}, {"E", 329.63},
            {"E#", 349.23}, {"Fb", 329.63}, {"F", 349.23}, {"F#", 369.99}, {"Gb", 369.99}, {"G", 392.0}, {"G#", 415.30},
            {"Ab", 415.30}, {"A", 440.0}, {"A#", 466.16}, {"Bb", 466.16}, {"B", 493.88}, {"B#", 523.25}, {"Cb", 261.63}
    };

    static auto et_tune = [](const Note& n) -> double {
        double freq = lookup_table.at(n.value_);
        return freq * std::pow(2, n.octave_ - 4);
    };

    static Temperament et(et_tune);

    return et;
}
