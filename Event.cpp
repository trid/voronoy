//
// Created by TriD on 09.05.2015.
//

#include "Event.h"

#include "EventTree.h"

extern int sweepingLineY;

void SiteEvent::process(EventTree *tree) {
    tree->add(&point);
    sweepingLineY = point.y;
}
