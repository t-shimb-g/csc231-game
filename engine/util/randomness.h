#pragma once

#include <random>
#include <stdexcept>
#include <algorithm>

static std::mt19937 random_engine{std::random_device{}()};
    
int randint(int min, int max);
bool probability(int percentage);
    
template <typename T>
auto& random_choice(T& container) {
    if (container.empty()) {
        throw std::runtime_error("Container is empty");
    }
    else if (container.size() == 1) {
        return *std::begin(container);
    }
    else {
        int index = randint(0, container.size()-1);
        auto it = std::next(std::begin(container), index);
        return *it;
    }
}

template <typename Iterator>
void shuffle(Iterator begin, Iterator end) {
    std::shuffle(begin, end, random_engine);
}
