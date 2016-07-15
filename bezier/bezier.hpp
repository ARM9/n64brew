#pragma once

#include "vector.hpp"

// N-degree bezier curve
template<unsigned N>
struct Bezier {
    Vec2<float> points[N+1];

    Vec2<float> draw(float t) {
        return draw(points, N+1, t);
    }

private:
    Vec2<float> draw(Vec2<float> *pts, unsigned len, float t) {
        if(len == 1) {
            return {pts[0].x, pts[0].y};
        } else {
            unsigned newlen = len - 1;
            Vec2<float> newpoints[newlen];
            for(unsigned i = 0; i < newlen; i++) {
                newpoints[i] = (1.f - t) * pts[i] + t * pts[i+1];
            }
            return draw(newpoints, newlen, t);
        }
    }
};

