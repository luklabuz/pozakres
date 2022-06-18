//
// Created by lukla on 16.06.2022.
//

#ifndef POZAKRES_RANDOM_HPP
#define POZAKRES_RANDOM_HPP

#include <random>

#include "melody.hpp"
#include "detail.hpp"

std::vector<Note> randomMelody(const TrackData&, double, double);

#endif //POZAKRES_RANDOM_HPP
