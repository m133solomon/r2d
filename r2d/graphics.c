#include "graphics.h"

void Rect_fill(SDL_Renderer *renderer, Rect *rect)
{
    SDL_RenderFillRect(renderer, (SDL_Rect*)rect);
}

void Rect_stroke(SDL_Renderer *renderer, Rect *rect, uint32_t weight)
{
    if (weight == 0)
    {
        return;
    }

    if (weight == 1)
    {
        SDL_RenderDrawRect(renderer, (SDL_Rect*)rect);
        return;
    }

    for (int i = 0; i < weight; i++)
    {
        int x = rect->x - i;
        int y = rect->y - i;
        int w = rect->w + i * 2;
        int h = rect->h + i * 2;
        SDL_Rect rect = { x, y, w, h };
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Line_stroke(SDL_Renderer *renderer, Line *line)
{
    SDL_RenderDrawLine(renderer, line->x1, line->y1, line->x2, line->y2);
}

void Circle_stroke(SDL_Renderer *renderer, Circle *circle)
{
    const int32_t diameter = (circle->r * 2);

    int32_t x = (circle->r - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, circle->x + x, circle->y - y);
        SDL_RenderDrawPoint(renderer, circle->x + x, circle->y + y);
        SDL_RenderDrawPoint(renderer, circle->x - x, circle->y - y);
        SDL_RenderDrawPoint(renderer, circle->x - x, circle->y + y);
        SDL_RenderDrawPoint(renderer, circle->x + y, circle->y - x);
        SDL_RenderDrawPoint(renderer, circle->x + y, circle->y + x);
        SDL_RenderDrawPoint(renderer, circle->x - y, circle->y - x);
        SDL_RenderDrawPoint(renderer, circle->x - y, circle->y + x);

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

void Circle_fill(SDL_Renderer *renderer, Circle *circle)
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
        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

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

