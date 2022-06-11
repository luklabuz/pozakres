#include <iostream>
#include <array>
#include "markov.hpp"
#include <random>

int main() {
    std::array<std::string, 4> a = {"dziekan", "skurwysyn", "robi", "loda"};
    std::array<std::array<double, 4>, 4> p = { {{0.75, 0.05, 0.15, 0.05},
                                                {0.3, 0.4, 0.15, 0.15},
                                                {0.0, 0.5, 0.3, 0.2},
                                                {0.25, 0.25, 0.25, 0.25}} };

    std::random_device rd;
    std::mt19937 mt(rd());
    MarkovProcess<std::string, 4> m(a, p, 1);

    for(int j = 0; j < 10; ++j) {
        for (int i = 0; i < 10; ++i)
            std::cout << m(mt) << ' ';
        std::cout << '\n';
    }

    return 0;
}
