#include "graphics.h"
#include "include/SDL2/SDL_render.h"

void Canvas_init(Canvas *canvas, SDL_Window *window)
{
    canvas->clear_color = (Color) { 50, 50, 50, 255 };
    canvas->renderer_flags = SDL_RENDERER_ACCELERATED;
    canvas->last_position = Vec2_NULL;
    canvas->position = (Vec2) { 0, 0 };
    canvas->renderer = SDL_CreateRenderer(window, -1, canvas->renderer_flags);
}

void Canvas_clear(Canvas *canvas)
{
    SDL_SetRenderDrawColor
    (
        canvas->renderer,
        canvas->clear_color.r,
        canvas->clear_color.g,
        canvas->clear_color.b,
        canvas->clear_color.a
    );
    SDL_RenderClear(canvas->renderer);

    LOG_INFO("hello da"); 
    LOG_ERROR("hello world");
}

void Canvas_present(Canvas *canvas)
{
    SDL_RenderPresent(canvas->renderer);
}

void Canvas_push_state(Canvas *canvas)
{
    if (Vec2_is_null(&canvas->last_position))
    {
        
    }
    canvas->last_position = canvas->position;
}

void Canvas_pop_state(Canvas *canvas)
{
    canvas->position = canvas->last_position;
}

void Canvas_set_clear_color(Canvas *canvas, Color color)
{
    canvas->clear_color = color;
}

void Canvas_set_fill_color(Canvas *canvas, Color color)
{
    SDL_SetRenderDrawColor(canvas->renderer, color.r, color.g, color.b, color.a);
}

void Canvas_fill_rect(Canvas *canvas, Rect *rect)
{
    SDL_RenderFillRect(canvas->renderer, (SDL_Rect*)rect);
}

void Canvas_stroke_rect(Canvas *canvas, Rect *rect, uint32_t weight)
{
    if (weight == 0)
    {
        return;
    }

    if (weight == 1)
    {
        SDL_RenderDrawRect(canvas->renderer, (SDL_Rect*)rect);
        return;
    }

    for (int i = 0; i < weight; i++)
    {
        int x = rect->x - i;
        int y = rect->y - i;
        int w = rect->w + i * 2;
        int h = rect->h + i * 2;
        SDL_Rect rect = { x, y, w, h };
        SDL_RenderDrawRect(canvas->renderer, &rect);
    }
}

void Canvas_stroke_line(Canvas *canvas, Line *line)
{
    SDL_RenderDrawLine(canvas->renderer, line->x1, line->y1, line->x2, line->y2);
}

void Canvas_stroke_circle(Canvas *canvas, Circle *circle)
{
    const int32_t diameter = (circle->r * 2);

    int32_t x = (circle->r - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(canvas->renderer, circle->x + x, circle->y - y);
        SDL_RenderDrawPoint(canvas->renderer, circle->x + x, circle->y + y);
        SDL_RenderDrawPoint(canvas->renderer, circle->x - x, circle->y - y);
        SDL_RenderDrawPoint(canvas->renderer, circle->x - x, circle->y + y);
        SDL_RenderDrawPoint(canvas->renderer, circle->x + y, circle->y - x);
        SDL_RenderDrawPoint(canvas->renderer, circle->x + y, circle->y + x);
        SDL_RenderDrawPoint(canvas->renderer, circle->x - y, circle->y - x);
        SDL_RenderDrawPoint(canvas->renderer, circle->x - y, circle->y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void Canvas_fill_circle(Canvas *canvas, Circle *circle)
{
    int x = circle->x;
    int y = circle->y;
    int radius = circle->r;

    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx)
    {
        status += SDL_RenderDrawLine(canvas->renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(canvas->renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(canvas->renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(canvas->renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2*offsetx)
        {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

