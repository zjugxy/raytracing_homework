#pragma once
#include<RAY.h>
#include<mymath.h>
#include<hitreord.h>

static float cospdf(const vec3& normal,const vec3& w_i){
        return glm::dot(glm::normalize(normal),glm::normalize(w_i))/PI;
    }

static float highlightpdf(const float& N,const vec3& w_i,const vec3& perfectout){
    return (N+2)/TWOPI*pow(glm::dot(glm::normalize(perfectout),glm::normalize(w_i)),N);
}

class myMaterial{
    public:
    virtual bool scatter(const Ray& rayin,const hitrecord& rec,vec3& attenuation,Ray& scatter,float& PDF)=0;
    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec) = 0;
};

class Diffuse:public myMaterial{
    public:
    vec3 Kd;
    Diffuse(float a,float b,float c):Kd(a,b,c){}

    virtual bool scatter(const Ray& w_o,const hitrecord& rec,vec3& attenuation,Ray& scatter,float& PDF)override{
        float rand1 = random_float(),rand2 = random_float();
        float theta = acos(sqrt(rand1));
        float phai = TWOPI*rand2;
        float x = sin(theta)*cos(phai),y = sin(theta)*sin(phai),z = cos(theta);

        vec3 z_axis = glm::normalize(rec.normal);
        vec3 help = vec3(0.0f,1.0f,0.0f);
        if(help==z_axis)
            help  = glm::normalize(vec3(0.0f,1.0f,1.0f));
        vec3 x_axis = glm::normalize(glm::cross(help, z_axis));
        vec3 y_axis = glm::normalize(glm::cross(z_axis, x_axis));

        vec3 w_i = x*x_axis+y*y_axis+z*z_axis;
        scatter = Ray(rec.position,w_i);
        attenuation = BRDF(w_i,w_o.dir,rec);

        PDF = cospdf(rec.normal,w_i);
        return true;
    }



    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        return Kd/PI;
    }
};

class Specular:public myMaterial{
    public:
    vec3 Kd,Ks;
    float Ns;
    Specular(vec3 kd,vec3 ks,float n):Kd(kd),Ks(ks),Ns(n){}

    virtual bool scatter(const Ray& rayin,const hitrecord& rec,vec3& attenuation,Ray& scatter,float& PDF)override{
        float randomnum = random_float();
        const float CUT = 0.4;
        float rand1 = random_float(),rand2 = random_float();
        vec3 w_i;
        //diffuse
        if(randomnum<CUT){
            float theta = acos(sqrt(rand1));
            float phai = TWOPI*rand2;
            float x = sin(theta)*cos(phai),y = sin(theta)*sin(phai),z = cos(theta);
            vec3 z_axis = glm::normalize(rec.normal);
            vec3 help = vec3(0.0f,1.0f,0.0f);
            if(help==z_axis)
                help  = glm::normalize(vec3(0.0f,1.0f,1.0f));
            vec3 x_axis = glm::normalize(glm::cross(help, z_axis));
            vec3 y_axis = glm::normalize(glm::cross(z_axis, x_axis));
            w_i = x*x_axis+y*y_axis+z*z_axis;
            PDF = cospdf(rec.normal,w_i);
        }
        else{//spec
            float theta = acos(pow(rand1,1.0f/(Ns+1.0f)));
            float phai = TWOPI*rand2;
            float x = sin(theta)*cos(phai),y = sin(theta)*sin(phai),z = cos(theta);
            vec3 perfect = glm::normalize(glm::reflect(rayin.dir,rec.normal));
            vec3 z_axis = perfect;
            vec3 help = vec3(0.0f,1.0f,0.0f);
            if(help==z_axis)
                help  = glm::normalize(vec3(0.0f,1.0f,1.0f));
            vec3 x_axis = glm::normalize(glm::cross(help, z_axis));
            vec3 y_axis = glm::normalize(glm::cross(z_axis, x_axis));
            w_i = x*x_axis+y*y_axis+z*z_axis;
            PDF = highlightpdf(Ns,w_i,perfect);
        }
        attenuation = BRDF(w_i,rayin.dir,rec);
        scatter = Ray(rec.position,w_i);
        return true;
    }

    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        vec3 perfectout = glm::reflect(w_in,rec.normal);
        float coselem = clamp(glm::dot(glm::normalize(w_out),glm::normalize(perfectout)),0.0f,1.0f);
        float elem = std::pow(coselem,Ns)*(Ns+2.0f)/TWOPI;
        return Kd/PI+elem*Ks;
    }



};

