//
// Created by lukla on 17.06.2022.
//

#ifndef POZAKRES_PLAYER_HPP
#define POZAKRES_PLAYER_HPP

#include <AudioFile.h>
#include <armadillo>
#include "detail.hpp"

class Player
{
    AudioFile<double> file_;

public:
    void fromTracks(TrackData, const std::vector<arma::dvec>&);
    void save(const std::string&);
};


#endif //POZAKRES_PLAYER_HPP
