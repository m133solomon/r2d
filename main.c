#include <stdbool.h>
#include <stdlib.h>

#include "r2d/r2d.h"

Application application;

void draw();
void init();

int main()
{
    application = Application_new();
    application.draw_func = draw;
    application.background_color = Color_new_rgb(0, 0, 0);
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
    Application_set_fill_color(&application, COLOR_BLUE);

    Circle_fill(application.renderer, &(Circle) { 100, 100, 100 });

    if (application.time_manager.delta_time != 0)
    {
        uint32_t fps = Application_get_fps(&application);
        char title[32];

        sprintf(title, "FPS: %d", fps);
        Application_set_window_title(&application, title);
    }
}
