//
// Created by Ryan Strauss on 12/9/19.
//

#ifndef BOIDS_BOID_H
#define BOIDS_BOID_H

#include <vector>
#include "Vector2D.h"

using Vector2D = utils::Vector2D<float>;
struct UpdateParams {
  float max_force{};
  float acceleration_scale{};
  float cohesion_weight{};
  float alignment_weight{};
  float separation_weight{};
  float separation_distance{};
  float noise_scale{};
};
class Boid {
public:
    Vector2D position, velocity;
    float max_speed;
    float perception;
    bool is_predator;

    // Constructors
    Boid(float x, float y, float max_speed,
         float perception, bool is_predator = false);

    void update(const Vector2D& world_size, const UpdateParams& params, const std::vector<Boid *> &boids);

    [[nodiscard]] float angle() const;

private:
  constexpr static float PREDATOR_ESCAPE_FACTOR = 10000000;

  constexpr static float PREDATOR_SPEED_BOOST = 1.8;
  constexpr static float PREDATOR_PERCEPTION_BOOST = 1.5;
  constexpr static float PREDATOR_ACCELERATION_BOOST = 1.4;

  [[nodiscard]] Vector2D alignment(const Vector2D& world_size, const std::vector<Boid *> &boids) const;
  [[nodiscard]] Vector2D cohesion(const Vector2D& world_size, const std::vector<Boid *> &boids) const;
  [[nodiscard]] Vector2D separation(const Vector2D& world_size, const UpdateParams& params, const std::vector<Boid *> &boids) const;
};


#endif //BOIDS_BOID_H
