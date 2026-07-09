#pragma once
#include <random>

inline float RandFloat(float min, float max) {
    static thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

inline float RandGaussian(float mean, float stddev) {
    static thread_local std::mt19937 gen{std::random_device{}()};
    std::normal_distribution<float> dist(mean, stddev);
    return dist(gen);
}
