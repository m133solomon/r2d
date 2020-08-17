#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdlib.h>

#include "include/SDL2/SDL.h"

#include "helper.h"
#include "color.h"
#include "mathematics.h"

typedef struct
{
    SDL_Renderer *renderer;
    Uint32 renderer_flags;

    Color clear_color;
    Color draw_color;

    Vec2 size;

    bool state_saved;
    Vec2 position;
    Vec2 last_position;
} Canvas;

void Canvas_init(Canvas *canvas, SDL_Window *window);
void Canvas_clear(Canvas *canvas);
void Canvas_present(Canvas *canvas);

void Canvas_push_state(Canvas *canvas);
void Canvas_pop_state(Canvas *canvas);

void Canvas_set_clear_color(Canvas *canvas, Color color);
void Canvas_set_fill_color(Canvas *canvas, Color color);

void Canvas_fill_rect(Canvas *canvas, Rect *rect);
void Canvas_stroke_rect(Canvas *canvas, Rect *rect, uint32_t weight);

void Canvas_stroke_line(Canvas *canvas, Line *line);

void Canvas_stroke_circle(Canvas *canvas, Circle *circle);
void Canvas_fill_circle(Canvas *canvas, Circle *circle);

#endif // GRAPHICS_H
