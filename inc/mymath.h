#pragma once

#include <glm/glm.hpp>
#include<random>
using vec3 = glm::vec3 ;
using Point = glm::vec3;
using Dir = glm::vec3;
using vec2 = glm::vec2;

vec3 random_vec3();
float random_float();
bool judge_equal(float elems[],float cmp);
float clamp(float value,float min,float max);
vec3 sample_tri();