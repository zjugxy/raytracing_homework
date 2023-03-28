#pragma once
#include<RAY.h>
#include<mymath.h>
#include<hitreord.h>
class myMaterial{
    public:
    virtual bool scatter(const Ray& rayin,const hitrecord& rec,vec3& attenuation,Ray& scatter)=0;
    virtual vec3 lightelem()const= 0;
    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out) = 0;
};

class Diffuse:public myMaterial{
    public:
    vec3 Kd;
    Diffuse(float a,float b,float c):Kd(a,b,c){}

    virtual bool scatter(const Ray& rayin,const hitrecord& rec,vec3& attenuation,Ray& scatter)override{
        vec3 dirrand = random_vec3();
        float sign = glm::dot(dirrand,rec.normal);
        while(sign<=0.001){
            dirrand = random_vec3();
            sign = glm::dot(dirrand,rec.normal);
        }   
        attenuation = Kd;
        scatter = Ray(rec.position,dirrand);
        return true;
    }

    virtual vec3 lightelem()const{
        return Kd;
    }

    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out)override{
        return Kd/3.14159f;
    }
};
