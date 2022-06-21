//
// Created by lukla on 18.06.2022.
//

#include "piece.hpp"

std::vector<arma::dvec> Piece::play()
{
    size_t duration = 0;
    for(const auto& note : std::get<1>(tracks_[0]))
        duration += note.duration_ * 60 * data_.sampleRate / bpm_;

    arma::dvec res(duration, arma::fill::zeros);

    for(auto& track : tracks_)
    {
        size_t last = 0;
        for(const auto& note : std::get<1>(track))
        {
            size_t dur = note.duration_ * 60 * data_.sampleRate / bpm_;
            res.subvec(last, last + dur - 1) += std::get<0>(track)(note, tmp_, bpm_, data_);
            last += dur;
        }
        res /= tracks_.size();
    }

    return std::vector<arma::dvec>(data_.channels, res);
}
