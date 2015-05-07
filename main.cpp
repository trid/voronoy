#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

using std::rand;
using std::sort;
using std::srand;
using std::time;
using std::vector;


class Point {
public:
    int x, y;
};

class Edge {
public:
    int x1, y1, x2, y2;
};

const int pointsCount = 10;
vector <Point> points(pointsCount);
SDL_Surface* surface;
SDL_Window* window;

void putPoints();

void generateBackground();

int getClosestPoint(int x, int y);

bool compare(const Point &, const Point &);

class Event{
    virtual void process() = 0;
    virtual int getY() = 0;
};

class SiteEvent: public Event {
    Point point;

    SiteEvent(Point& point): point(point) {}

    virtual void process() override {}

    virtual int getY() override { return point.y; }
};

class CircleEvent: public Event {

};

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