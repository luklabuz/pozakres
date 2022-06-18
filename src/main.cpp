#include <iostream>

#include "random.hpp"
#include "melody.hpp"
#include "player.hpp"
#include "instrument.hpp"
#include "wave.hpp"
#include "piece.hpp"

int main() {

    TrackData td = {4410, 2, 24, 2};
    std::vector<Note> melody = randomMelody(td, 60.0, 60.0);
    Player p;
    AdditiveSynth in({ {Sine(), 1.0, 1.0}, {Sine(), 2.0, 0.5} }, {0.1, 0.1, 0.7, 0.1});

    Piece piece(equal_temperament(), 60.0, td, { {in, melody} });

    for(const auto& note : melody)
    {
        std::cout << note.value_ << static_cast<int>(note.octave_) << ": " << note.duration_ << '\n';
    }

    p.fromTracks(td, piece.play());

    p.save("randompiece2.wav");

    return 0;
}
