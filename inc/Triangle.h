#pragma once
#include <mymath.h>
#include "AABB.h"
#include<RAY.h>
#include<hitreord.h>
#include<cmath>

class Triangle {
public:
    vec3 vertices[3];
    vec3 normals[3];
    vec2 texs[3];
    size_t mtlindex;
    Triangle(const vec3& v0, const vec3& v1, const vec3& v2,const vec3& n0, const vec3& n1, const vec3& n2,const vec2& t0, const vec2& t1, const vec2& t2,size_t index);
    bool intersect(const Ray& ray,double t_min,double t_max,hitrecord& rec)const;
    AABB get_bbox()const;
    Triangle() = default;
    bool calculate_fromuv(const vec3& coord,vec3& position,vec3& normal)const;
    bool calculate_fromuv(const vec3& coord,vec3& position,vec3& normal,vec2& texcoord)const;
};