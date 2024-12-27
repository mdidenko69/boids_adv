//
// Created by Maxim Didenko on 12/27/24.
//
#include "random.h"
#include <random>

namespace utils {
  static auto& randGenerator() {
    static thread_local std::mt19937 generator(std::random_device{}());
    return generator;
  }
  int random(int min, int max) {
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(randGenerator());
  }
  float random(float min, float max) {
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(randGenerator());
  }
}