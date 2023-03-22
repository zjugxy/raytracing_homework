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
        forward = glm::normalize(lookat - eye);
        right = glm::normalize(glm::cross(forward, up));
        up_vec = glm::normalize(glm::cross(right, forward));

        fov_radians = fov * M_PI / 180.0;
        half_height = glm::tan(fov_radians / 2.0);
        aspect_ratio = (float)width / height;
        half_width = aspect_ratio * half_height;
        lower_left_corner = eye - right*half_width-up_vec*half_height+forward;
    }

    vec3 Camera::front(){
        return lookat - eye; 
    }


    Ray Camera::castray(float s, float t)
    {
        vec3 origin = eye;
        vec3 direction = lower_left_corner+s*2*half_width*right+t*2*half_height*up_vec-eye;
        return Ray(origin, direction);
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