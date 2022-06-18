//
// Created by lukla on 18.06.2022.
//

#include <random>

#include "random.hpp"
#include "markov.hpp"

std::vector<Note> randomMelody(const TrackData& data, double length, double bpm)
{
    auto beats = static_cast<uint32_t>(bpm * length / 60);

    MarkovProcess<int, 3> mp = { {0, 1, 2},
                                 {{{0.7, 0.3, 0.0},
                                   {0.2, 0.4, 0.4},
                                   {0.4, 0.4, 0.2}}},
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
            res.push_back({value(random()), 4, 1.0, static_cast<double>(duration)});
            beat--;
            continue;
        }
    }

    return res;
}
