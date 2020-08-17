#include "graphics.h"
#include "mathematics.h"

void Canvas_init(Canvas *canvas, SDL_Window *window)
{
    canvas->clear_color = (Color) { 50, 50, 50, 255 };
    canvas->renderer_flags = SDL_RENDERER_ACCELERATED;
    canvas->state_saved = false;
    canvas->last_position = (Vec2) { 0, 0 };
    canvas->position = (Vec2) { 0, 0 };
    canvas->renderer = SDL_CreateRenderer(window, -1, canvas->renderer_flags);
}

void Canvas_clear(Canvas *canvas)
{
    // dont forget to reset the transformations;
    canvas->position = (Vec2) { 0, 0 };
    canvas->last_position = (Vec2) { 0, 0 };

    SDL_SetRenderDrawColor
    (
        canvas->renderer,
        canvas->clear_color.r,
        canvas->clear_color.g,
        canvas->clear_color.b,
        canvas->clear_color.a
    );
    SDL_RenderClear(canvas->renderer);
}

void Canvas_present(Canvas *canvas)
{
    SDL_RenderPresent(canvas->renderer);
}

void Canvas_push_state(Canvas *canvas)
{
    if (canvas->state_saved)
    {
        LOG_ERROR("Canvas: Cannot call push again before pop (probably 2 consecutive pushes)");
        return;
    }
    canvas->state_saved = true;
    canvas->last_position = canvas->position;
}

void Canvas_pop_state(Canvas *canvas)
{
    if (!canvas->state_saved)
    {
        LOG_WARN("Canvas: state already popped (probably 2 consecutive pops)");
        return;
    }
    canvas->state_saved = false;
    canvas->position = canvas->last_position;
}

void Canvas_translate(Canvas *canvas, int x, int y)
{
    canvas->position.x = x;
    canvas->position.y = y;
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
    SDL_Rect draw_rect;
    draw_rect.x = canvas->position.x + rect->x;
    draw_rect.y = canvas->position.y + rect->y;
    draw_rect.w = rect->w;
    draw_rect.h = rect->h;
    SDL_RenderFillRect(canvas->renderer, &draw_rect);
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
            LOG_ERROR("Canvas: error filling circle (graphics.c: Canvas_fill_circle");
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

