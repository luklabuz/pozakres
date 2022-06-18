//
// Created by lukla on 18.06.2022.
//

#ifndef POZAKRES_PIECE_HPP
#define POZAKRES_PIECE_HPP

#include <utility>
#include <armadillo>

#include "melody.hpp"
#include "detail.hpp"
#include "instrument.hpp"

class Piece
{
    using Tracks = std::vector<std::pair<Instrument, std::vector<Note>>>;

    Temperament tmp_;
    double bpm_;
    TrackData data_;
    Tracks tracks_;

public:
    Piece(Temperament  tmp_, double bpm_, const TrackData& data_, Tracks tracks_) :
        tmp_(std::move(tmp_)), bpm_(bpm_), data_(data_), tracks_(std::move(tracks_)) {}

    [[nodiscard]] std::vector<arma::dvec> play();

};

#endif //POZAKRES_PIECE_HPP
