#include <SDL3/SDL.h>
#include <iostream>
#include "../src/types.h"
#include "../src/xy.h" // TODO: probably bad practice
// TODO: how to do slider and reset button?

#ifndef VIS_H
#define VIS_H

uint32_t colorMap(float value) {
    float r, g, b;
    r = fabs(sin(value));
    g = fabs(sin(value + M_PI / 3.0));
    b = fabs(sin(value + 2.0 * M_PI / 3.0));
    return 0xFF000000 | (static_cast<Uint8>(r * 255)<<16) | (static_cast<Uint8>(g * 255)<<8) | static_cast<Uint8>(b * 255);
}


class Visualizer {
    public:
        Visualizer(ModelSettings&, float);
        ~Visualizer();
        bool init();
        void draw(Grid&);
    private:
        ModelSettings* settings;
        float scale;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        uint32_t* pixels = nullptr;
};

Visualizer::~Visualizer() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Visualizer::Visualizer(ModelSettings& settings, float scale)
    : settings(&settings), scale(scale) { init(); }

bool Visualizer::init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        "Vis", settings->grid_size * scale, settings->grid_size * scale,
        0, &window, &renderer
    );
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, settings->grid_size, settings->grid_size);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderDrawColorFloat(renderer, 0., 0., 0., 1.);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    pixels = new uint32_t[settings->grid_size * settings->grid_size];
    return true;
}

void Visualizer::draw(Grid& grid) {
    for (int i = 0; i < settings->grid_size; i++) {
        for (int j = 0; j < settings->grid_size; j++) {
            pixels[i * settings->grid_size + j] = colorMap(grid[j][i]);
        }
    }
    SDL_UpdateTexture(texture, NULL, pixels, settings->grid_size * sizeof(uint32_t));
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

#endif
