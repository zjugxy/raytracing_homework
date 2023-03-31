#pragma once

#include <glm/glm.hpp>
#include<random>
using vec3 = glm::vec3 ;
using Point = glm::vec3;
using Dir = glm::vec3;
using vec2 = glm::vec2;
#define PI 3.1415926f
#define TWOPI 6.2831853f
vec3 random_vec3();
float random_float();
bool judge_equal(float elems[],float cmp);
float clamp(float value,float min,float max);
vec3 sample_tri();
inline double random_double();
float random_in_range(float,float);
float powerweight(const float& weight1,const float& weight2);