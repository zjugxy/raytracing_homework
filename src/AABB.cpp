#include<AABB.h>

vec3 AABB::max()const{
        return maxpoint;
    }

vec3 AABB::min()const{
        return minpoint;
    }

AABB& AABB::MergeAABB(AABB aabb){
    float x,y,z;
    x = aabb.min().x<minpoint.x?aabb.min().x:minpoint.x;
    y = aabb.min().y<minpoint.y?aabb.min().y:minpoint.y;
    z = aabb.min().z<minpoint.z?aabb.min().z:minpoint.z;
    vec3 newmin(x,y,z);

    x = aabb.max().x>maxpoint.x?aabb.max().x:maxpoint.x;
    y = aabb.max().y>maxpoint.y?aabb.max().y:maxpoint.y;
    z = aabb.max().z>maxpoint.z?aabb.max().z:maxpoint.z;
    vec3 newmax(x,y,z);
    minpoint = newmin;
    maxpoint = newmax;
    return *this;
}

void AABB::MergePoint(vec3& point){

    float x=point.x,y = point.y,z = point.z;
    if(x>maxpoint.x)
        maxpoint.x=x;
    if(x<minpoint.x)
        minpoint.x = x;
    
    if(y>maxpoint.y)
        maxpoint.y=y;
    if(y<minpoint.y)
        minpoint.y = y;

    if(z>maxpoint.z)
        maxpoint.z=z;
    if(z<minpoint.z)
        minpoint.z = z;

}

//min,max list
AABB::AABB():minpoint(9999999.,9999999.,9999999.),maxpoint(-99999999.,-99999999.,-99999999.){
    
}

AABB::AABB(float x,float y,float z,float a,float b,float c):minpoint(x,y,z),maxpoint(a,b,c){

}

AABB::AABB(vec3 minp,vec3 maxp):minpoint(minp),maxpoint(maxp){

}

AABB::AABB(vec3 point1,vec3 point2,vec3 point3){
    float x = findmin(point1.x,point2.x,point3.x);
    float y = findmin(point1.y,point2.y,point3.y);
    float z = findmin(point1.z,point2.z,point3.z);
    minpoint = vec3(x,y,z);

    x = findmax(point1.x,point2.x,point3.x);
    y = findmax(point1.y,point2.y,point3.y);
    z = findmax(point1.z,point2.z,point3.z);
    maxpoint = vec3(x,y,z);
}

void AABB::printInfo(){
    std::cout<<"the min point is"<<minpoint.x<<' '<<minpoint.y<<' '<<minpoint.z<<std::endl;
    std::cout<<"the max point is"<<maxpoint.x<<' '<<maxpoint.y<<' '<<maxpoint.z<<std::endl;
}

void testAABB(){
    AABB a(1,2,3,4,5,6);
    AABB b(vec3(-1,-2,-3),vec3(-3,-5,-7),vec3(0,2,3));
    std::cout<<"info of a"<<std::endl;
    a.printInfo();
    std::cout<<"info of b"<<std::endl;
    b.printInfo();



    AABB d(vec3(1,2,3),vec3(4,5,6));
    std::cout<<"info of d"<<std::endl;
    (d.MergeAABB(a)).printInfo();
    return;
}

AABB from_points(vec3 vertices[],int num){
    if(num<3)
        throw std::logic_error("error in num func fromPoint");
    AABB ret(vertices[0],vertices[1],vertices[2]);
    int i=3;
    for(;i<num;i++){
        ret.MergePoint(vertices[i]);
    }
    return ret;
}

int AABB::get_longest_axis(){
        float x = maxpoint.x-minpoint.x;
        float y = maxpoint.y-minpoint.y;
        float z = maxpoint.z-minpoint.z;
        if(x>y&&x>z)
            return 0;
        else if(y>z)
            return 1;
        else
            return 2;
    }

vec3 AABB::get_centroid()const{
    auto mid = maxpoint+minpoint;
    mid.x/=2;
    mid.y/=2;
    mid.z/=2;
    return mid;
}

bool AABB::intersect(const Ray& ray,float tmin,float tmax)const{
    for(int i=0;i<3;i++){
        if(ray.dir[i]==0){
            if(ray.orig[i]>maxpoint[i]||ray.orig[i]<minpoint[i])
                return false;
        }
        else{
            float t0 = (minpoint[i] - ray.orig[i]) / ray.dir[i];
            float t1 = (maxpoint[i] - ray.orig[i]) / ray.dir[i];
            if (t0 > t1) std::swap(t0, t1);
            // Check if slab intersection intervals overlap
            if (t0 > tmin) tmin = t0;
            if (t1 < tmax) tmax = t1;
            if (tmin > tmax) {
                return false; // Ray misses AABB
            }
        }
    
    }
    return true;
}

static inline float findmin(float& a,float& b,float& c){
    if(a<=b&&a<=c)
        return a;
    else if(b<=c)
        return b;
    else    
        return c;
}

static inline float findmax(float& a,float& b,float& c){
    if(a>=b&&a>=c)
        return a;
    else if(b>=c)
        return b;
    else    
        return c;
}