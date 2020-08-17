#ifndef APPLICATION_H
#define APPLICATION_H

/*
 * Execrable game engine by m133solomon
 * Built with fucking C
 * Should have:
 *
 * - shapes: stroke / fill
 * - sprite sheet animation
 * - camera / zoom / window resize
 * - tweens
 * - ecs
 * - basic shape intersection
 * - shaders
 * - scene manager
 * - small ui library
 * - basic particle systems
 *
 * - big boi step:
 *   -- BIND TO FUCKING JAVASCRIPT
 */

/*
 * HOW IT SHOULD WORK:
 * - huge mf application struct
 *   handles input audio canvas etc
 *
 * - another huge canvas class
 *   for graphoics
 *   - primitives
 *   - fill stroke
 *   - shaders
 *   - camera
 */

#include "include/SDL2/SDL.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "helper.h"
#include "color.h"
#include "mathematics.h"
#include "graphics.h"

typedef struct
{
    Uint64 last;
    Uint64 now;
    Uint64 delta_time;
} TimeManager;

void TimeManager_tick(TimeManager *time_manager);

typedef struct
{
    Vec2 screen_size;

    Color background_color;
    Color fill_color;

    TimeManager time_manager;

    Uint32 window_flags;

    SDL_Window *window;

    Canvas canvas;

    void (*draw_func)();

    char *title;
} Application;

Application Application_new();

void Application_init(Application *application);
void Application_cleanup(Application *application);
void Application_loop(Application *application);

float Application_get_delta_time(Application *application);
uint32_t Application_get_fps(Application *application);

void Application_set_window_title(Application *application, char * title);

#endif // APPLICATION_H
