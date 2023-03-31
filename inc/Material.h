#pragma once
#include<RAY.h>
#include<mymath.h>
#include<hitreord.h>
#include<Texture.h>
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
    virtual float MTLPDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec) = 0;
    bool has_Kdmap = false;
    myTexture* texture = nullptr;
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

    virtual float MTLPDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        return cospdf(rec.normal,w_in);
    }

    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        if(has_Kdmap)
            return  texture->getUV(rec.texcoord[0],rec.texcoord[1])/PI;
        else
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

        if(has_Kdmap)
            return  texture->getUV(rec.texcoord[0],rec.texcoord[1])/PI+elem*Ks;
        else
            return Kd/PI+elem*Ks;
    }

    virtual float MTLPDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        const float CUT = 0.4;
        if(random_float()<CUT){
            return   cospdf(rec.normal,w_in);
        }
        else{
            vec3 perfect = glm::normalize(glm::reflect(w_out,rec.normal));
            return   highlightpdf(Ns,w_in,perfect);
        }
    }

};

class Glass:public myMaterial{
    public:
    vec3 diffuse;
    vec3 transparent;
    float Ni;
    float CUT = 0.8;//根据transparent 计算
    Glass(vec3 diff,vec3 trans,float N):diffuse(diff),transparent(trans),Ni(N){}


    virtual bool scatter(const Ray& rayin,const hitrecord& rec,vec3& attenuation,Ray& scatter,float& PDF){
        float randnum = random_float();
        float sign = (glm::dot(rayin.dir,rec.normal)<0)?1:-1;
        //sign < 0  从空气至介质 >0 从介质至空气
        if(randnum>CUT){
            //diffuse
        float rand1 = random_float(),rand2 = random_float();
        float theta = acos(sqrt(rand1));
        float phai = TWOPI*rand2;
        float x = sin(theta)*cos(phai),y = sin(theta)*sin(phai),z = cos(theta);

        vec3 z_axis = glm::normalize(rec.normal);
        z_axis*=sign;
        vec3 help = vec3(0.0f,1.0f,0.0f);
        if(help==z_axis)
            help  = glm::normalize(vec3(0.0f,1.0f,1.0f));
        vec3 x_axis = glm::normalize(glm::cross(help, z_axis));
        vec3 y_axis = glm::normalize(glm::cross(z_axis, x_axis));

        vec3 w_i = x*x_axis+y*y_axis+z*z_axis;
        scatter = Ray(rec.position,w_i);
        attenuation = diffuse/PI;
        PDF = cospdf(z_axis,w_i);
        return true;
        }
        else{
            //refraction
            vec3 dir = glm::normalize(rayin.dir);
            vec3 recnorm = glm::normalize(rec.normal);
            float sintheta1 = abs(glm::dot(dir,recnorm));
            float costheta1 = sqrt(1-sintheta1*sintheta1);
            float sintheta2 = sign<0?sintheta1/Ni:sintheta1*Ni;
      
            if(sintheta2>1){
                //全反射
                vec3 w_i = glm::reflect(dir,-1.0f*recnorm);
                scatter = Ray(rec.position,w_i);
                attenuation = diffuse;
                PDF = 1;
                return true;
            }
            else{
                float costheta2 = sqrt(1 - sintheta2 * sintheta2);
                vec3 w_t = (sign < 0) ? (sintheta2 * (-recnorm) + costheta2 * (dir + sintheta1 * recnorm)) / Ni : 
                (sintheta2 * (-recnorm) + costheta2 * (dir - sintheta1 * recnorm)) * Ni;
                scatter = Ray(rec.position, w_t);
                attenuation = transparent;
                PDF = 1.0f;
                return true;
            }
        }

    }
    virtual float MTLPDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        return 1.0f;
    }

    virtual vec3 BRDF(const vec3& w_in,const vec3& w_out,const hitrecord& rec)override{
        return transparent;
    }
};