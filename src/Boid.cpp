//
// Created by Ryan Strauss on 12/9/19.
//

#include <cmath>
#include "Boid.h"

Boid::Boid(float x, float y, float max_speed,
           float perception, bool is_predator) {

    this->max_speed = max_speed;
    this->perception = perception;
    this->is_predator = is_predator;

    if (is_predator) {
        this->max_speed *= PREDATOR_SPEED_BOOST;
        this->perception *= PREDATOR_PERCEPTION_BOOST;
    }
    position = Vector2D{x, y};
    velocity = (Vector2D::random() - 0.5) * max_speed * 2;
}

Vector2D Boid::alignment(const Vector2D& world_size, const std::vector<Boid *> &boids) const {
    Vector2D perceived_velocity;
    int n = 0;

    for (const Boid *b: boids) {
        if (this != b) {
            if (b->is_predator)
                return Vector2D{};

            perceived_velocity += b->velocity;
            ++n;
        }
    }

    if (n == 0)
        return {};

    perceived_velocity /= n;
    Vector2D steer = perceived_velocity - velocity;
    return steer.normalize();
}

Vector2D Boid::cohesion(const Vector2D& world_size, const std::vector<Boid *> &boids) const {
    Vector2D perceived_center;
    int n = 0;

    for (const Boid *b: boids) {
        if (this != b) {
            if (b->is_predator)
                return Vector2D{};

            perceived_center += b->position;
            ++n;
        }
    }

    if (n == 0)
        return {};

    perceived_center /= n;
    Vector2D steer = perceived_center - position;
    return steer.normalize();
}

Vector2D Boid::separation(const Vector2D& world_size, const UpdateParams& params, const std::vector<Boid *> &boids) const {
    Vector2D c;

    for (const auto* b: boids) {
        if (this != b) {
            if (!is_predator && b->is_predator) {
                return (b->position - position).normalize() * -PREDATOR_ESCAPE_FACTOR;
            } else if (is_predator == b->is_predator &&
                       position.toroidal_distance2(b->position, world_size.x, world_size.y) <
                       params.separation_distance * params.separation_distance) {
                c -= b->position - position;
            }
        }
    }

    return c.normalize();
}

void Boid::update(const Vector2D& world_size, const UpdateParams& params, const std::vector<Boid *> &boids) {
    // Apply each rule, get resulting forces, and weight them
    Vector2D alignment_update = alignment(world_size, boids) * params.alignment_weight;
    Vector2D cohesion_update = cohesion(world_size, boids) * params.cohesion_weight;
    Vector2D separation_update = separation(world_size, params, boids) * params.separation_weight;
    // Apply the weighted forces to this boid
    Vector2D acceleration = alignment_update + cohesion_update + separation_update;
    // Scale the acceleration then use it to update the velocity
    if (is_predator)
        acceleration *= PREDATOR_ACCELERATION_BOOST;
    acceleration *= params.acceleration_scale;
    acceleration.limit(params.max_force);
    velocity += acceleration;
    if (params.noise_scale != 0)
        velocity += (Vector2D::random() - 0.5) * params.noise_scale;
    // Limit the velocity so the boids don't get too fast
    velocity.limit(max_speed);
    // Then update the position based on the velocity
    position += velocity;
    // If boid leaves the screen, update position so the boid wraps around
    if (position.x < 0) position.x += world_size.x;
    if (position.y < 0) position.y += world_size.y;
    if (position.x >= world_size.x) position.x -= world_size.x;
    if (position.y >= world_size.y) position.y -= world_size.y;
}

float Boid::angle() const {
    return (float) (atan2(velocity.x, -velocity.y) * 180 / M_PI);
}
