#include "r2d.h"
#include "include/SDL2/SDL_render.h"

void TimeManager_tick(TimeManager *time_manager)
{
    time_manager->now = SDL_GetTicks();
    time_manager->delta_time = time_manager->now - time_manager->last;
    time_manager->last = time_manager->now;
}

Application Application_new()
{
    Application application;
    application.screen_size = (Vec2){ 400, 400 };
    application.title = "C game engine";
    application.time_manager = (TimeManager){ 0, 0, 0 };
    application.window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    application.renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    application.background_color = Color_new_rgb(50, 50, 50);
    return application;
}

void Application_init(Application *application)
{
    application->window =
        SDL_CreateWindow
        (
            application->title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            application->screen_size.x, application->screen_size.y,
            application->window_flags
        );

    application->renderer = SDL_CreateRenderer(application->window, -1, application->renderer_flags);
}

void Application_cleanup(Application *application)
{
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
    SDL_Quit();
}

void Application_loop(Application *application)
{
    bool quit = false;

    while (!quit)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        TimeManager_tick(&application->time_manager);

        SDL_SetRenderDrawColor
        (
            application->renderer,
            application->background_color.r,
            application->background_color.g,
            application->background_color.b,
            application->background_color.a
        );
        SDL_RenderClear(application->renderer);

        application->draw_func();

        SDL_RenderPresent(application->renderer);
    }

    Application_cleanup(application);
}

void Application_set_window_title(Application *application, char * title)
{
    application->title = title;
    SDL_SetWindowTitle(application->window, title);
}

float Application_get_delta_time(Application *application)
{
    if (application->time_manager.delta_time == 0)
    {
        return 0.0f;
    }

    return application->time_manager.delta_time / 1000.0f;
}

uint32_t Application_get_fps(Application *application)
{
    if (application->time_manager.delta_time == 0)
    {
        return 0;
    }

    return 1 / (application->time_manager.delta_time / 1000.0f);
}

void Application_set_fill_color(Application *application, Color color)
{
    application->fill_color = color;
    SDL_SetRenderDrawColor(application->renderer, color.r, color.g, color.b, color.a);
}
