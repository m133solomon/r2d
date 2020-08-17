#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <stdlib.h>
#include <stdbool.h>

int Random_int(int min, int max);

typedef struct
{
    int x;
    int y;
} Vec2;

const Vec2 Vec2_NULL;

bool Vec2_is_null(Vec2 *vec);

Vec2 Vec2_add(Vec2 *u, Vec2 *v);
Vec2 Vec2_substract(Vec2 *u, Vec2 *v);
Vec2 Vec2_mult(Vec2 *u, Vec2 *v);
Vec2 Vec2_divide(Vec2 *u, Vec2 *v);

typedef struct
{
    int x;
    int y;
    int w;
    int h;
} Rect;

typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
} Line;

typedef struct
{
    int x;
    int y;
    int r;
} Circle;


#endif // MATHEMATICS_H
