//
// Created by TriD on 09.05.2015.
//

#ifndef VORONOY_EVENTTREE_H
#define VORONOY_EVENTTREE_H

#include "Event.h"


class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;

    Point* data;
    int breakpoint;

    TreeNode(Point* point): data(point) {}
    bool isLeaf() { return left || right; }
    void add(Point* point);
};


class EventTree {
public:
    TreeNode* root = nullptr;

    void add(Point* point);
};


#endif //VORONOY_EVENTTREE_H
