//
// Created by lukla on 17.06.2022.
//

#ifndef POZAKRES_DETAIL_HPP
#define POZAKRES_DETAIL_HPP

#include <random>

struct TrackData
{
    int sampleRate;
    int length;
    int bitDepth;
    int channels;
};

std::mt19937& random();

#endif //POZAKRES_DETAIL_HPP
