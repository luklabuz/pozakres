//
// Created by lukla on 16.06.2022.
//

#ifndef POZAKRES_RANDOM_HPP
#define POZAKRES_RANDOM_HPP

#include <random>

std::mt19937& random()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    return mt;
}

#endif //POZAKRES_RANDOM_HPP
