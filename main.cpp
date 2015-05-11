#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>

#include <SDL2/SDL.h>

#include "Point.h"
#include "Event.h"
#include "Edge.h"
#include "EventTree.h"

using std::rand;
using std::sort;
using std::srand;
using std::time;
using std::vector;
using std::priority_queue;


const int pointsCount = 10;
vector <Point> points(pointsCount);
SDL_Surface* surface;
SDL_Window* window;

EventTree tree;

void putPoints();

void generateBackground();

int getClosestPoint(int x, int y);

bool compare(const Point &, const Point &);

priority_queue<Event*, vector<Event*>, CompareEvents> events;

int sweepingLineY = 0;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Renderer* renderer;

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);

    srand(time(nullptr));

    putPoints();
    generateBackground();

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    while (true) {
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                return 0;
            }
        }
    }

    return 0;
}

void generateBackground() {
    surface = SDL_CreateRGBSurface(SDL_GetWindowPixelFormat(window), 800, 600, 32, 0, 0, 0, 0);

    for (Point point: points) {
        events.push(new SiteEvent(point));
    }

    while (!events.empty()) {
        Event *event = events.top();
        event->process(&tree);
        events.pop();
        delete event;
    }
}


int getClosestPoint(int x, int y) {
    int closestDist = (points[0].x - x) * (points[0].x - x) + (points[0].y - y) * (points[0].y - y);
    int closestIndex = 0;

    for (int i = 1; i < pointsCount; i++) {
        int dist = (points[i].x - x) * (points[i].x - x) + (points[i].y - y) * (points[i].y - y);
        if (dist < closestDist) {
            closestDist = dist;
            closestIndex = i;
        }
    }

    return closestIndex;
}

void putPoints() {
    for (int i = 0; i < pointsCount; i++) {
        points[i].x = rand() % 800;
        points[i].y = rand() % 600;
    }
    sort(points.begin(), points.end(), compare);
}

bool compare(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}
