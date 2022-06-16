//
// Created by lukla on 11.06.2022.
//

#ifndef POZAKRES_MARKOV_HPP
#define POZAKRES_MARKOV_HPP

#include <array>
#include <random>

template<class T, std::size_t N>
class MarkovProcess
{
    class MarkovChain
    {
    public:
        using AdjacencyMatrix = std::array<std::array<double, N>, N>;
        using distribution_type = MarkovProcess<T, N>;

    private:
        std::array<T, N> states_;
        AdjacencyMatrix probabilities_;

    public:
        MarkovChain() = default;
        MarkovChain(const std::array<T, N>& s, const AdjacencyMatrix& p)
                : states_(s), probabilities_(p){}
        MarkovChain(const MarkovChain& other)
                : MarkovChain(other.states_, other.probabilities_) {}
        MarkovChain& operator=(const MarkovChain& other)
        {
            if(this != &other)
            {
                states_ = other.states_;
                probabilities_ = other.probabilities_;
            }
            return *this;
        }

        bool operator==(const MarkovChain& rhs)
        {
            return (states_ == rhs.states_ &&
                    probabilities_ == rhs.probabilities_);
        }

        bool operator!=(const MarkovChain& rhs)
        {
            return !(*this == rhs);
        }

        friend class MarkovProcess;
    };

    MarkovChain chain_;
    std::size_t current_;
    std::array<std::discrete_distribution<unsigned long long>, N> dist_;

public:
    using result_type = T;
    using param_type = std::pair<MarkovChain, std::size_t>;

    MarkovProcess() : chain_({}), current_(0), dist_({}) {}
    MarkovProcess(const std::array<T, N>& states, const typename MarkovChain::AdjacencyMatrix& prob,
                  std::size_t start) : chain_(MarkovChain(states, prob)), current_(start), dist_({}) {
        std::transform(chain_.probabilities_.begin(), chain_.probabilities_.end(), dist_.begin(),
                       [](const std::array<double, N>& r){
            return std::discrete_distribution<unsigned long long>(r.begin(), r.end());
                    });
    }
    MarkovProcess(const MarkovProcess& other)
        : MarkovProcess(other.chain_.states_, other.chain_.probabilities, other.current_) {}

    MarkovProcess& operator=(const MarkovProcess& other)
    {
        if(this != &other)
        {
            chain_ = other.chain_;
            current_ = other.current_;
            dist_ = other.dist_;
        }
        return *this;
    }

    param_type param()
    {
        return {chain_, current_};
    }

    bool operator==(const MarkovProcess& rhs)
    {
        return (chain_ == rhs.chain_ &&
                current_ == rhs.current_ &&
                dist_ == rhs.dist_);
    }

    bool operator!=(const MarkovProcess& rhs)
    {
        return !(*this == rhs);
    }

    result_type min()
    {
        return *chain_.states_.begin();
    }

    result_type max()
    {
        return *chain_.states_.rbegin();
    }

    template<std::uniform_random_bit_generator G>
    result_type operator()(G& gen)
    {
        current_ = dist_[current_](gen);
        return chain_.states_[current_];
    }

    template<std::uniform_random_bit_generator G>
    result_type operator()(G& gen, param_type param)
    {
        std::discrete_distribution<unsigned long long> dist(param.first.probabilities_[param.second]);
        return param.first.states_[dist(gen)];
    }
};



#endif //POZAKRES_MARKOV_HPP
