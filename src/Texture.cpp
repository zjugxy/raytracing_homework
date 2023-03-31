#include <Texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include<iostream>
myTexture::myTexture()
{
}
myTexture::~myTexture()
{
}
myTexture::myTexture(std::string texture_fullpath)
{
    auto image = stbi_load(texture_fullpath.c_str(), &width, &height, &channels, 0);
    image_data = std::vector<unsigned char>(image, image + width * height * channels);
}
vec3 myTexture::getUV(float u, float v)
{
    if(u>1.0f){
        u-=1.0f;
    }
    if(u<0.0f){
        u+=1.0f;
    }
    if(v>1.0f){
        v-=1.0f;
    }
    if(v<0.0f){
        v+=1.0f;
    }

    int x = u * width;
    int y = v * height;
    if(x==width)
        x-=1;
    if(y==height)
        y-=1;
    int index = (y * width + x) * channels;
    
    unsigned char r = image_data[index];
    unsigned char g = image_data[index + 1];
    unsigned char b = image_data[index + 2];
    return vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}