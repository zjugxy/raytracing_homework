#pragma once

#include<mymath.h>
#include <string>
class myTexture
{
public:
    int width, height, channels;
    std::vector<unsigned char> image_data;
    myTexture();
    ~myTexture();
    myTexture(std::string texture_fullpath);
    vec3 getUV(float u, float v);
};