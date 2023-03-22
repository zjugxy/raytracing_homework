#pragma once
#include<mymath.h>
#include<string>
#include<RAY.h>

class Camera{
    private:
    Point eye;
    vec3 lookat;
    vec3 up;
    float fov;

    vec3 forward,right,up_vec;
    float fov_radians,half_height,aspect_ratio,half_width;
    std::string type;
    vec3 lower_left_corner;
    public:
    int width,height;

    Camera(const char* type,int wid,int hei,float fov,
    float eyex,float eyey,float eyez,
    float lookatx,float lookaty,float lookatz,
    float upx,float upy,float upz
    );
    
    // void Copy(Camera& another);

    Camera()=default;
    // Ray castray(int x,int y);
    vec3 front();
    Ray castray(float s, float t);
};