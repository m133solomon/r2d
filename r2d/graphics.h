#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdlib.h>

#include "include/SDL2/SDL.h"

#include "mathematics.h"

void Rect_fill(SDL_Renderer *renderer, Rect *rect);
void Rect_stroke(SDL_Renderer *renderer, Rect *rect, uint32_t weight);

void Line_stroke(SDL_Renderer *renderer, Line *line);

void Circle_stroke(SDL_Renderer *renderer, Circle *circle);
void Circle_fill(SDL_Renderer *renderer, Circle *circle);

#endif // GRAPHICS_H
