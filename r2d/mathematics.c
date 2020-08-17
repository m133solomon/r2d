#include "mathematics.h"

int Random_int(int min, int max)
{
    return (rand() % (min - max + 1)) + min;
}

bool Vec2_is_null(Vec2 *vec)
{
    return vec->x == Vec2_NULL.x && vec->y == Vec2_NULL.y;
}

Vec2 Vec2_add(Vec2 *u, Vec2 *v)
{
    Vec2 result;
    result.x = u->x + v->x;
    result.y = u->y + v->y;
    return result;
}

Vec2 Vec2_substract(Vec2 *u, Vec2 *v)
{
    Vec2 result;
    result.x = u->x - v->x;
    result.y = u->y - v->y;
    return result;
}

Vec2 Vec2_mult(Vec2 *u, Vec2 *v)
{
    Vec2 result;
    result.x = u->x * v->x;
    result.y = u->y * v->y;
    return result;
}

Vec2 Vec2_divide(Vec2 *u, Vec2 *v)
{
    Vec2 result;
    result.x = u->x / v->x;
    result.y = u->y / v->y;
    return result;
}

