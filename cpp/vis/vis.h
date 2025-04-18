#include <SDL3/SDL.h>
#include <iostream>
#include "../src/types.h"
#include "../src/xy.h"

#ifndef VIS_H
#define VIS_H

uint32_t colorMap(float angle, float colormap_angle) {
    float r, g, b;
    angle = fmod(angle + colormap_angle, 2 * M_PI);
    float hPrime = (angle/(2.0 * M_PI) * 6);
    float x = (1-fabs(fmod(hPrime, 2.0) - 1));
    switch (static_cast<int>(hPrime) % 6) {
        case 0: r = 1; g = x; b = 0; break;
        case 1: r = x; g = 1; b = 0; break;
        case 2: r = 0; g = 1; b = x; break;
        case 3: r = 0; g = x; b = 1; break;
        case 4: r = x; g = 0; b = 1; break;
        case 5: r = 1; g = 0; b = x; break;
    }

    return 0xFF000000 | (static_cast<uint8_t>(r * 255) << 16) |
                         (static_cast<uint8_t>(g * 255) << 8)  |
                         static_cast<uint8_t>(b * 255);
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
            pixels[i * settings->grid_size + j] = colorMap(grid[j][i], settings->colormap_angle);
        }
    }
    SDL_UpdateTexture(texture, NULL, pixels, settings->grid_size * sizeof(uint32_t));
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

#endif
