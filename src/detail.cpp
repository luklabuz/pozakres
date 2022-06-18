//
// Created by lukla on 18.06.2022.
//

#include "detail.hpp"

std::mt19937& random()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    return mt;
}
