#include<AABB.h>

vec3 AABB::max()const{
        return maxpoint;
    }

vec3 AABB::min()const{
        return minpoint;
    }

AABB AABB::MergeAABB(AABB& aabb){
    float x,y,z;
    x = aabb.min().x<minpoint.x?aabb.min().x:minpoint.x;
    y = aabb.min().y<minpoint.y?aabb.min().y:minpoint.y;
    z = aabb.min().z<minpoint.z?aabb.min().z:minpoint.z;
    vec3 newmin(x,y,z);

    x = aabb.max().x>maxpoint.x?aabb.max().x:maxpoint.x;
    y = aabb.max().y>maxpoint.y?aabb.max().y:maxpoint.y;
    z = aabb.max().z>maxpoint.z?aabb.max().z:maxpoint.z;
    vec3 newmax(x,y,z);
    return AABB(newmin,newmax);
}


//min,max list
AABB::AABB(float x,float y,float z,float a,float b,float c):minpoint(x,y,z),maxpoint(a,b,c){

}

AABB::AABB(){}

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

    AABB c = a.MergeAABB(b);
    std::cout<<"info of c"<<std::endl;
    c.printInfo();

    AABB d(vec3(1,2,3),vec3(4,5,6));
    std::cout<<"info of d"<<std::endl;
    (d.MergeAABB(a)).printInfo();
    return;
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