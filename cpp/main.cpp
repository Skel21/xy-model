#include "./vis/vis.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_hints.h>
#include <iostream>
#include "./src/types.h"
#include "./src/xy.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/bind.h>
#endif


ModelSettings *settings;
XYModel *model;
Visualizer *vis;


void main_loop()
{
    model->step();
    vis->draw(model->grid);
}

void init()
{
#ifdef __EMSCRIPTEN__
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR, "#simulation");
#endif
    settings = new ModelSettings();
    settings->temperature = 1.0;
    settings->grid_size = 100;
    settings->anisotropy = 0.0;
    model = new XYModel(*settings);
    vis = new Visualizer(*settings, 4);
}

void reset()
{
    model->initialize();
    vis->draw(model->grid);
}

void set_temperature(double temperature) {
    settings->temperature = temperature;
}

void set_anisotropy(double anisotropy) {
    settings->anisotropy = anisotropy;
}

void set_external_field(double external_field) {
    settings->external_field = external_field;
}

void set_colormap_angle(double angle) {
    settings->colormap_angle = angle;
}

#ifdef __EMSCRIPTEN__

void play_pause(bool paused)
{
    if (paused)
    {
        emscripten_cancel_main_loop();
    }
    else
    {
        emscripten_set_main_loop(main_loop, 0, 1);
    }
}

void set_main_loop()
{
    emscripten_set_main_loop(main_loop, 0, 1);
}

EMSCRIPTEN_BINDINGS()
{
    emscripten::function("init", &init);
    emscripten::function("reset", &reset);
    emscripten::function("main_loop", &main_loop);
    emscripten::function("set_main_loop", &set_main_loop);
    emscripten::function("set_temperature", &set_temperature);
    emscripten::function("play_pause", &play_pause);
    emscripten::function("set_anisotropy", &set_anisotropy);
    emscripten::function("set_external_field", &set_external_field);
    emscripten::function("set_colormap_angle", &set_colormap_angle);
};
#endif

#ifndef __EMSCRIPTEN__
int main()
{
    init();
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        main_loop();
    }
    return 0;
}
#endif
