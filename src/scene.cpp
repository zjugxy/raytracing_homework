#include"scene.h"

bool Scene::loadobj(const char*filename,const char* basefile,bool triangulate){
    std::cout << "Loading " << filename << std::endl;

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename,
                              basefile, triangulate);

    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }

    if (!ret) {
        printf("Failed to load/parse .obj.\n");
        return false;
    }

    std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
    std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
    std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2)
                << std::endl;
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;
    
    //set light
    is_light.resize(materials.size());
    for(auto&elem:is_light)
        elem = 0;

    return true;

}

bool Scene::loadxml(const char* filename){
    tinyxml2::XMLDocument doc;
    
    std::cout<<"Loadfile "<<filename<<std::endl;
    auto error = doc.LoadFile(filename);
    if(error!=tinyxml2::XML_SUCCESS){
        std::cout<<"error filename or broken file"<<std::endl;
        printf("ERROR: %s",doc.ErrorStr());
        return false;
    }
    //camera process
    auto root = doc.RootElement();

    auto xmlcamera = root;  
    //auto xmlcamera = doc.FirstChildElement("camera");
    auto eye= xmlcamera->FirstChildElement("eye");
    auto lookat = xmlcamera->FirstChildElement("lookat");
    auto up = xmlcamera->FirstChildElement("up");

    camera = Camera(
        xmlcamera->Attribute("type"),xmlcamera->IntAttribute("width"),xmlcamera->IntAttribute("height"),xmlcamera->FloatAttribute("fovy"),
        eye->FloatAttribute("x"),eye->FloatAttribute("y"),eye->FloatAttribute("z"),
        lookat->FloatAttribute("x"),lookat->FloatAttribute("y"),lookat->FloatAttribute("z"),
        up->FloatAttribute("x"),up->FloatAttribute("y"),up->FloatAttribute("z")
    );

    //light process the elem in doc

    for(auto elem = root->NextSiblingElement();elem!=nullptr;elem=elem->NextSiblingElement()){
        if(std::string(elem->Name())=="light"){
            auto mtlname = elem->Attribute("mtlname");
            auto radiancestr = elem->Attribute("radiance");
    //cmp with the materials loaded in obj file
            int _start=0,_end = materials.size();
            for(;_start!=_end;_start++){
                if(materials[_start].name==mtlname){
                    //match radiance with material id
                    is_light[_start] = 1;
                    float x,y,z;
                    sscanf(radiancestr,"%f,%f,%f",&x,&y,&z);
                    radiance[_start] = vec3(x,y,z);
                    break;
                }
            }
            if(_start==_end){
                throw std::logic_error("unmatched light with material");
                return false;
            }
        }
        else{
            throw std::logic_error("elem unexpected");
            return false;
        }
    }
    return true;
}

