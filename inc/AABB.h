#pragma once
#include<mymath.h>
#include<iostream>

class AABB{
    private:
    vec3 minpoint;
    vec3 maxpoint;

    public:
    vec3 max()const;
    vec3 min()const;

    AABB MergeAABB(AABB& aabb);
    AABB() = default;
    AABB(float x,float y,float z,float a,float b,float c);//min,max list
    AABB(vec3 point1,vec3 point2,vec3 point3);
    AABB(vec3 minp,vec3 maxp);
    void printInfo();
};

void testAABB();
static inline float findmin(float& a,float& b,float& c);
static inline float findmax(float& a,float& b,float& c);