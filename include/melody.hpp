//
// Created by lukla on 17.06.2022.
//

#ifndef POZAKRES_MELODY_HPP
#define POZAKRES_MELODY_HPP

#include <string>
#include <functional>

struct Note;
class Temperament;

Temperament& equal_temperament();

struct Note
{
    std::string value_;
    int8_t octave_;
    double volume_;
    double duration_;
};

class Temperament
{
    std::function<double (const Note&)> tune_;
public:
    explicit Temperament(std::function<double (const Note&)> tune_) : tune_(std::move(tune_)) {}
    double operator()(const Note& n) const
    {
        return tune_(n);
    }
};

#endif //POZAKRES_MELODY_HPP
