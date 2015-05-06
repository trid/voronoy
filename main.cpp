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
    SDL_Color color;
    vector<Point*> connections;
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
};

class SiteEvent: public Event {

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

//void generateBackground() {
//    surface = SDL_CreateRGBSurface(SDL_GetWindowPixelFormat(window), 800, 600, 32, 0, 0, 0, 0);
//
//    for (int x = 0; x < 800; x ++) {
//        for (int y = 0; y < 600; y++) {
//            SDL_Color point = points[getClosestPoint(x, y)].color;
//            ((Uint32*)surface->pixels)[y * 800 + x] = SDL_MapRGB(surface->format, point.r, point.g, point.b);
//        }
//    }
//}

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
        points[i].color.r = (Uint8) (rand() / 256);
        points[i].color.g = (Uint8) (rand() / 256);
        points[i].color.b = (Uint8) (rand() / 256);
        points[i].color.a = (Uint8) 255;
    }
    sort(points.begin(), points.end(), compare);
}

bool compare(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}