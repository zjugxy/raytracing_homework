#pragma once
#include<mymath.h>

struct hitrecord
{
    vec3 position;
    vec3 normal;
    vec2 texcoord;
    int materialid;
    double t=99999999.0;//length of ray
};