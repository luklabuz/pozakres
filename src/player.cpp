//
// Created by lukla on 17.06.2022.
//

#include "player.hpp"

void Player::fromTracks(TrackData data_, const std::vector<arma::dvec>& tracks_)
{
    file_.setSampleRate(data_.sampleRate);
    file_.setBitDepth(data_.bitDepth);

    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(tracks_.size());
    for(int i = 0; i < buffer.size(); ++i)
        buffer[i] = arma::conv_to<std::vector<double>>::from(tracks_[i]);
    file_.setAudioBuffer(buffer);
}

void Player::save(const std::string& path_)
{
    file_.save(path_, AudioFileFormat::Wave);
}
