#include <stdbool.h>
#include <stdlib.h>

#include "r2d/graphics.h"
#include "r2d/mathematics.h"
#include "r2d/r2d.h"

#include "r2d/include/SDL2/SDL_opengl.h"

Application application;

void draw();
void init();

int main()
{
    application = Application_new();
    application.draw_func = draw;
    application.screen_size = (Vec2) { 800, 600 };
    Application_init(&application);

    init();
    Application_loop(&application);

    return 0;
}

void init()
{
}

void draw()
{
    Canvas_set_fill_color(&application.canvas, COLOR_YELLOW);
    Canvas_fill_rect(&application.canvas, &((Rect) { 100, 100, 100, 100 }));

    if (application.time_manager.delta_time != 0)
    {
        uint32_t fps = Application_get_fps(&application);
        char title[32];

        sprintf(title, "FPS: %d", fps);
        Application_set_window_title(&application, title);
    }
}
