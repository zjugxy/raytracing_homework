#pragma once
#include<mymath.h>
#include<iostream>
#include<RAY.h>
#include<hitreord.h>

class AABB{
    private:
    vec3 minpoint;
    vec3 maxpoint;

    public:
    vec3 max()const;
    vec3 min()const;

    static AABB from_points(vec3 vertices[],int num);
    AABB& MergeAABB(AABB aabb);

    void MergePoint(vec3& point);
    AABB();
    AABB(float x,float y,float z,float a,float b,float c);//min,max list
    AABB(vec3 point1,vec3 point2,vec3 point3);
    AABB(vec3 minp,vec3 maxp);
    void printInfo();
    int get_longest_axis();
    vec3 get_centroid()const;
    bool intersect(const Ray& ray,float tmin,float tmax)const;

};

void testAABB();
static inline float findmin(float& a,float& b,float& c);
static inline float findmax(float& a,float& b,float& c);