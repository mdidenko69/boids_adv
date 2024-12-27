//
// Created by Ryan Strauss on 12/9/19.
//

#ifndef BOIDS_BOID_H
#define BOIDS_BOID_H

#include <vector>
#include "Vector2D.h"

using Vector2D = utils::Vector2D<float>;
class Boid {
private:
    constexpr static float PREDATOR_ESCAPE_FACTOR = 10000000;

    constexpr static float PREDATOR_SPEED_BOOST = 1.8;
    constexpr static float PREDATOR_PERCEPTION_BOOST = 1.5;
    constexpr static float PREDATOR_ACCELERATION_BOOST = 1.4;

public:
    Vector2D position, velocity;
    float max_width, max_height;
    float max_speed, max_force;
    float acceleration_scale;
    float cohesion_weight, alignment_weight, separation_weight;
    float perception, separation_distance;
    float noise_scale;
    bool is_predator;

    // Constructors
    Boid(float x, float y, float max_width, float max_height, float max_speed, float max_force,
         float acceleration_scale, float cohesion_weight, float alignment_weight, float separation_weight,
         float perception, float separation_distance, float noise_scale, bool is_predator = false);

    // Methods
    Vector2D alignment(const std::vector<Boid *> &boids) const;

    Vector2D cohesion(const std::vector<Boid *> &boids) const;

    Vector2D separation(const std::vector<Boid *> &boids) const;

    void update(const std::vector<Boid *> &boids);

    float angle() const;

};


#endif //BOIDS_BOID_H
