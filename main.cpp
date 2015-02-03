#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>

using std::rand;

class Point {
public:
    int x, y;
    SDL_Color color;
};

const int pointsCount = 128;
Point points[pointsCount];
SDL_Surface* surface;
SDL_Window* window;

void putPoints();

void generateBackground();

int getClosestPoint(int x, int y);

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Renderer* renderer;

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);

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

    for (int x = 0; x < 800; x ++) {
        for (int y = 0; y < 600; y++) {
            SDL_Color point = points[getClosestPoint(x, y)].color;
            ((Uint32*)surface->pixels)[y * 800 + x] = SDL_MapRGB(surface->format, point.r, point.g, point.b);
        }
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
        points[i].color.r = (Uint8) (rand() / 256);
        points[i].color.g = (Uint8) (rand() / 256);
        points[i].color.b = (Uint8) (rand() / 256);
        points[i].color.a = (Uint8) 255;
    }
}