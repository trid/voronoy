//
// Created by TriD on 09.05.2015.
//

#ifndef VORONOY_EVENT_H
#define VORONOY_EVENT_H


#include "Point.h"

class EventTree;

class Event{
public:
    virtual void process(EventTree *tree) = 0;
    virtual int getY() const = 0;
};

class SiteEvent: public Event {
private:
    Point point;
public:
    SiteEvent(Point& point): point(point) {}

    virtual void process(EventTree *tree) override;

    virtual int getY() const override { return point.y; }
};

class CircleEvent: public Event {

};

class CompareEvents{
public:
    bool operator() (const Event* e1, const Event* e2) {
        return e1->getY() > e2->getY();
    }
};

#endif //VORONOY_EVENT_H
