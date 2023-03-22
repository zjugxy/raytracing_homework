#pragma once
#include<Triangle.h>

struct Light{
    public:
    Triangle tri;
    vec3 radiance;
    float area;
    Light(Triangle& tri,vec3 rad):tri(tri),radiance(rad){
        glm::vec3 AB = tri.vertices[1] - tri.vertices[0];
        glm::vec3 AC = tri.vertices[2] - tri.vertices[0];
        vec3 N = glm::cross(AB,AC);
        area = glm::length(N)/2.0f;
    };
    //调用默认构造函数，一般不用特地写析构函数，拷贝构造，拷贝赋值都不用考虑
};