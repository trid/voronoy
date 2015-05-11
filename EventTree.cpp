//
// Created by TriD on 09.05.2015.
//

#include "EventTree.h"

void EventTree::add(Point* point) {
    if (!root) {
        root = new TreeNode(point);
    }
}

void TreeNode::add(Point *point) {
    if (isLeaf()) {
        if (point->x < data->x) {
            left = new TreeNode(point);
        }
        else {
            right = new TreeNode(point);
        }
        return;
    }
    else {
    }
}
