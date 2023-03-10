#pragma once
#include<mymath.h>



#include<tiny_obj_loader.h>

#include<tinyxml2.h>
#include<iostream>
#include<camera.h>
#include<stdexcept>

class BVHNode;
class Scene{
    public:
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::vector<int> is_light;//correspond to materials;
    //use a map to map the materials id to radiance
    std::map<int,vec3> radiance;

    Camera camera;

    //Camera camera;
    bool loadobj(const char* filename,const char* basefile,bool triangulate = true);
    //set camera and mark light
    bool loadxml(const char* filename);
    Scene() = default;
    BVHNode* buildBVH();
};