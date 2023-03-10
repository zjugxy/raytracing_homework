#include<camera.h>
    Camera::Camera(const char* type,int wid,int hei,float fov,
    float eyex,float eyey,float eyez,
    float lookatx,float lookaty,float lookatz,
    float upx,float upy,float upz
    ):type(type),width(wid),height(hei)
    ,eye(eyex,eyey,eyez)
    ,lookat(lookatx,lookaty,lookatz)
    ,up(upx,upy,upz)
    {
        
    }

    vec3 Camera::front(){
        return lookat - eye; 
    }

    // void Camera::Copy(Camera& another){
    //     type = std::string(another.type);
    //     width = another.width;
    //     height = another.height;
    //     eye = another.eye;
    //     lookat = another.lookat;
    //     up = another.up;
    // }
    // Ray camera::castray(int x,int y){

    // }