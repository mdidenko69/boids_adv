//
// Created by Ryan Strauss on 6/30/20.
//

#ifndef BOIDS_KDTREE_H
#define BOIDS_KDTREE_H

#include <vector>
#include <memory>
#include "Boid.h"

class KDTree {
public:
    KDTree(float width, float height);

    void insert(Boid *boid);

    std::vector<Boid *> search(Boid *query) const;

private:
    struct Node {
        using NodePtr = std::shared_ptr<Node>;

        NodePtr left, right;
        Boid *boid;
        bool vertical;

        Node(Boid *boid, bool vertical, const NodePtr &left, const NodePtr &right);

        bool isLeaf() const;
    };

    float width, height;
    Node::NodePtr root;

    static Node::NodePtr insert(const Node::NodePtr &node, Boid *boid, bool vertical);

    void search(Boid *query, const Node::NodePtr &node, std::vector<Boid *> &results) const;
};


#endif //BOIDS_KDTREE_H
