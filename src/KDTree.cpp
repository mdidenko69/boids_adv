//
// Created by Ryan Strauss on 6/30/20.
//

#include <cmath>
#include "KDTree.h"


KDTree::Node::Node(Boid *boid, bool vertical, const Node::NodePtr &left, const Node::NodePtr &right)
    : boid(boid), vertical(vertical), left(left), right(right) {}

bool KDTree::Node::isLeaf() const {
    return !left && !right;
}

KDTree::KDTree(float width, float height) : width{width}, height {height} {}

KDTree::Node::NodePtr KDTree::insert(const Node::NodePtr &node, Boid *boid, bool vertical) {
    if (!node) {
        return std::make_shared<Node>(boid, vertical, nullptr, nullptr);
    }

    if ((node->vertical && boid->position.x < node->boid->position.x) ||
        (!node->vertical && boid->position.y < node->boid->position.y)) {
        node->left = insert(node->left, boid, !node->vertical);
    } else {
        node->right = insert(node->right, boid, !node->vertical);
    }

    return node;
}

void KDTree::insert(Boid *boid) {
    root = insert(root, boid, true);
}

void KDTree::search(Boid *query, const Node::NodePtr &node, std::vector<Boid *> &results) const {

    double w = query->position.toroidal_distance2(node->boid->position, this->width, this->height);
    double radius = query->perception;

    if (w < radius * radius) {
        results.push_back(node->boid);
    }
    if (node->isLeaf()) {
        return;
    }

    double qx = query->position.x;
    double nx = node->boid->position.x;
    double qy = query->position.y;
    double ny = node->boid->position.y;

    if (node->vertical) {
        if (qx < nx) {
            if (qx - radius <= nx && node->left != nullptr) {
                search(query, node->left, results);
            }
            if (qx + radius > nx && node->right != nullptr) {
                search(query, node->right, results);
                return;
            }
        } else {
            if (qx + radius > nx && node->right != nullptr) {
                search(query, node->right, results);
            }
            if (qx - radius <= nx && node->left != nullptr) {
                search(query, node->left, results);
                return;
            }
        }
    } else {
        if (qy < ny) {
            if (qy - radius <= ny && node->left != nullptr) {
                search(query, node->left, results);
            }
            if (qy + radius > ny && node->right != nullptr) {
                search(query, node->right, results);
                return;
            }
        } else {
            if (qy + radius > ny && node->right != nullptr) {
                search(query, node->right, results);
            }
            if (qy - radius <= ny && node->left != nullptr) {
                search(query, node->left, results);
                return;
            }
        }
    }
}

std::vector<Boid *> KDTree::search(Boid *query) const {
    std::vector<Boid *> results;
    search(query, root, results);
    return results;
}
