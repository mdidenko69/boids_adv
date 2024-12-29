//
// Created by Ryan Strauss on 12/10/19.
//

#include "Flock.h"
#include "KDTree.h"

Boid Flock::operator[](int i) const {
    return boids[i];
}

void Flock::add(const Boid &boid) {
    boids.emplace_back(boid);
}

void Flock::clear() {
    boids.clear();
}

void Flock::update(const Vector2D& world_size, const UpdateParams& params, int num_threads) {
    // std::vector<Boid*> pboids;
    // pboids.reserve(boids.size());
    // for (auto& b: boids) {pboids.push_back(&b);}
    // for (auto& b: boids) { b.update(pboids);}

    KDTree tree(world_size.x, world_size.y);
    for (Boid &b: boids) tree.insert(&b);

    std::vector<Boid *> search_results[boids.size()];

//#pragma omp parallel for schedule(dynamic) num_threads(num_threads) if (num_threads > 1)
    for (int i = 0; i < boids.size(); ++i) {
        Boid &b = boids[i];
        search_results[i] = tree.search(&b);
    }

//#pragma omp parallel for schedule(dynamic) num_threads(num_threads) if (num_threads > 1)
    for (int i = 0; i < boids.size(); ++i)
        boids[i].update(world_size, params, search_results[i]);
}

int Flock::size() const {
    return boids.size();
}
