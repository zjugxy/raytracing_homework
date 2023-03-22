#ifndef RAY_H
#define RAY_H
#include<mymath.h>


class Ray {
    public:
        Ray() {}
        Ray(const vec3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}
        vec3 origin() const  { return orig; }
        vec3 direction() const { return dir; }
        vec3 at(float t) const {
            return orig + t*dir;
        }

    public:
        vec3 orig;
        vec3 dir;
};

#endif