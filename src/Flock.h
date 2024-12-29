//
// Created by Ryan Strauss on 12/10/19.
//

#ifndef BOIDS_FLOCK_H
#define BOIDS_FLOCK_H

#include <vector>
#include "Boid.h"

class Flock {
private:
    std::vector<Boid> boids;

public:

    Boid operator[](int i) const;
    void add(const Boid &boid);
    void clear();

    void update(const Vector2D& world_size, const UpdateParams& params, int num_threads = -1);

    int size() const;

};


#endif //BOIDS_FLOCK_H
