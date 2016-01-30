#ifndef VECTOR_H
#define VECTOR_H
#include "integer.h"

typedef struct {
    int x, y;
} Vec2;

typedef struct {
    int x, y, z;
} Vec3;

void vec2Set(Vec2 *v, fixed x, fixed y);
void vec2Add(Vec2 *a, Vec2 *b, Vec2 *c);
void vec2Sub(Vec2 *a, Vec2 *b, Vec2 *c);
void vec2Mul(Vec2 *a, Vec2 *b, Vec2 *c);
fixed vec2Dot(Vec2 *a, Vec2 *b);
fixed vec2Cross(Vec2 *a, Vec2 *b);

void vec3Set(Vec3 *v, fixed x, fixed y, fixed z);
void vec3Add(Vec3 *a, Vec3 *b, Vec3 *c);
void vec3Sub(Vec3 *a, Vec3 *b, Vec3 *c);
void vec3Mul(Vec3 *a, Vec3 *b, Vec3 *c);
fixed vec3Dot(Vec3 *a, Vec3 *b);
void vec3Cross(Vec3 *a, Vec3 *b, Vec3 *c);

#endif
