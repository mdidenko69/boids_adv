//
// Created by Maxim Didenko on 12/27/24.
//

#ifndef BOIDS_RANDOM_H
#define BOIDS_RANDOM_H

namespace utils {
  int random(int min, int max);
  inline int random(int max) {
    return random(0, max);
  }
  float random(float min, float max);
  inline float random(float max) {
    return random(0.0f, max);
  }
}

#endif //BOIDS_RANDOM_H
