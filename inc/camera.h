#pragma once
#include<mymath.h>
#include<string>

class Ray;
class Camera{
    private:
    Point eye;
    vec3 lookat;
    vec3 up;
    float fov;
    int width,height;
    
    std::string type;

    public:
    Camera(const char* type,int wid,int hei,float fov,
    float eyex,float eyey,float eyez,
    float lookatx,float lookaty,float lookatz,
    float upx,float upy,float upz
    );
    
    // void Copy(Camera& another);

    Camera()=default;
    // Ray castray(int x,int y);
    vec3 front();
};