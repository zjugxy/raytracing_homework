#pragma once
#include<Triangle.h>
#include<algorithm>
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

class LightSource{
    public:
    //scene 中的 map id既可以查询对应的 radiance
    std::vector<int> lightsid;
    std::vector<float> areavec;
    float totalarea;

    LightSource(){
        totalarea = 0;
    }

    int SampleLight(){
        float randnum = random_in_range(0.0f,totalarea);
        auto it = std::lower_bound(areavec.begin(),areavec.end(),randnum);
        if(it == areavec.end()){
            std::cout<<"error occur!"<<std::endl;
            return -1;
        }
        else    
            return lightsid[it-areavec.begin()]; 
    }
};