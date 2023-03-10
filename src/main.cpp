#include<iostream>
#include <vector>
#include<string>
#include<scene.h>
#include<AABB.h>


int main(){
    Scene myscene;

    const char* filename = "../example/cornell-box/cornell-box.obj";
    const char* basefile = "../example/cornell-box/";//used to find mtl file
    const char* xmlfile = "../example/cornell-box/cornell-box.xml";
    //load obj first to match the material with xml file
    myscene.loadobj(filename,basefile);
    myscene.loadxml(xmlfile);
    testAABB();

    //test input
    // {
    // std::cout<<"camera's front";
    // std::cout<<myscene.camera.front().x<<myscene.camera.front().y
    // <<myscene.camera.front().z<<std::endl;
    // std::cout<<myscene.radiance.size();
    // for(auto&elem:myscene.radiance){
    //     std::cout<<elem.first<<"radiance"<<elem.second.x<<elem.second.y
    //     <<elem.second.z;
    // }
    // }
}