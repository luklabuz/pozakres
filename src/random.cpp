//
// Created by lukla on 18.06.2022.
//

#include <random>

#include "wave.hpp"
#include "random.hpp"
#include "markov.hpp"

AdditiveSynth randomAdditiveSynth()
{
    static std::array<Oscillator, 4> waves = {Sine(), Sawtooth(), Triangle(), Square()};
    static std::uniform_int_distribution dist(0, 3);
    static std::uniform_int_distribution dist2(1, 10);
    static std::uniform_real_distribution<double> dist3(0.3, 0.8);
    static std::discrete_distribution<int> dist4({40, 10, 20, 10});

    int osc = dist(random()) + 1;

    std::vector<std::tuple<Oscillator, double, double>> oscs;
    for(int i = 1; i <= osc; ++i)
        oscs.emplace_back(waves.at(dist4(random())), static_cast<double>(std::pow(i, 2)), 1.0 / std::pow(i, 2));

    ADSR adsr = {
            dist2(random()) * 0.01, dist2(random()) * 0.01, dist3(random()), dist2(random()) * 0.01
    };

    return {oscs, adsr};
}

std::vector<Note> randomMelody(const TrackData& data, double length, double bpm)
{
    auto beats = static_cast<uint32_t>(bpm * length / 60);

    MarkovProcess<int, 3> mp = { {0, 1, 2},
                                 {{{0.6, 0.4, 0.0},
                                   {0.1, 0.5, 0.4},
                                   {0.3, 0.5, 0.2}}},
                                   0 };
    MarkovProcess<std::string, 7> value = {
            {"A", "B", "C", "D", "E", "F", "G"},
            {{
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                {0.4, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}
            }},
            0
    };

    std::vector<int> rhythm(beats);
    for(auto& beat : rhythm)
        beat = mp(random());

    std::vector<Note> res;
    int duration;
    for(int beat = 0; beat < beats; ++beat)
    {
        if(rhythm[beat] == 0)
        {
            duration = 1;
            while(rhythm[beat] == 0)
            {
                duration++;
                beat++;
            }
            res.push_back({"", 0, 0.0, static_cast<double>(duration - 1)});
            beat--;
            continue;
        }
        if(rhythm[beat] == 1)
        {
            duration = 1;
            beat++;
            while(rhythm[beat] == 2)
            {
                duration++;
                beat++;
            }
            res.push_back({value(random()), 4, 0.5, static_cast<double>(duration)});
            beat--;
            continue;
        }
    }

    return res;
}

FilteredNoise randomNoise(double sampleRate)
{
    static std::uniform_int_distribution dist(4, 9);
    static std::uniform_int_distribution dist2(1, 5);
    static std::uniform_int_distribution dist3(0, 60);
    static std::uniform_int_distribution dist4(1, 3);

    return {
            WhiteNoise(),
            LowPassFilter(sampleRate, dist(random()) * 100.0),
            Sine(dist2(random()) * 0.1, dist3(random()) * 0.1, dist4(random()) * 100.0)
    };
}

Piece randomPiece(const TrackData& data, double length)
{
    double bpm = std::uniform_int_distribution<int>(5, 9)(random()) * 10.0;
    static std::uniform_int_distribution dist(1, 5);

    return {
            equal_temperament(),
            bpm,
            data,
            {
                    {
                        randomAdditiveSynth(),
                        randomMelody(data, length, bpm)
                    },
                    {
                        randomNoise(static_cast<double>(data.sampleRate)),
                        {{"", 0, 0.2, static_cast<double>(static_cast<uint32_t>(bpm * length / 60))}}
                    }
            }
    };

}

