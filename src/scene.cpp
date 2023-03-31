#include "scene.h"

bool Scene::loadobj(const char *filename, const char *basefile, bool triangulate)
{
    std::cout << "Loading " << filename << std::endl;

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename,
                                basefile, triangulate);

    if (!warn.empty())
    {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty())
    {
        std::cerr << "ERR: " << err << std::endl;
    }

    if (!ret)
    {
        printf("Failed to load/parse .obj.\n");
        return false;
    }

    std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
    std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
    std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2)
              << std::endl;
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;

    // set light
    is_light.resize(materials.size());
    for (auto &elem : is_light)
        elem = 0;

    // set materials
    mymaterials.resize(materials.size());
    int matindex = 0;
    for (auto &mat : materials)
    {
        // 先处理diffuse
        if (judge_equal(mat.specular, 0.0) && mat.ior==1.0)
        {
            auto ptr = std::make_shared<Diffuse>(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
            mymaterials[matindex] = std::static_pointer_cast<myMaterial>(ptr);
        }
        else if (mat.ior==1.0f)
        {
            auto ptr = std::make_shared<Specular>(
                vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]),
                vec3(mat.specular[0], mat.specular[1], mat.specular[2]),
                mat.shininess);
            mymaterials[matindex] = std::static_pointer_cast<myMaterial>(ptr);
        }
        else
        {
            std::cout << "not diffuse mat occured" << std::endl;
            std::cout << mat.name;
            //because tinyobjload can not read Tr as a vec3, I define it the value of glass
            auto ptr = std::make_shared<Glass>(
                vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]),
                vec3(0.8f,1.0f,0.95f),
                mat.ior);
            std::cout << mat.transmittance[0] << mat.transmittance[1] << mat.transmittance[2];
            mymaterials[matindex] = std::static_pointer_cast<myMaterial>(ptr);
        }
        //加入Kd纹理
        if (!mat.diffuse_texname.empty())
        {
            mymaterials[matindex]->has_Kdmap = true;
            std::string texpath = basefile + mat.diffuse_texname;
            std::cout << "loading " << texpath << std::endl;
            mymaterials[matindex]->texture = new myTexture(texpath);
        }
        matindex++;
    }
    return true;
}

bool Scene::loadxml(const char *filename)
{
    tinyxml2::XMLDocument doc;

    std::cout << "Loadfile " << filename << std::endl;
    auto error = doc.LoadFile(filename);
    if (error != tinyxml2::XML_SUCCESS)
    {
        std::cout << "error filename or broken file" << std::endl;
        printf("ERROR: %s", doc.ErrorStr());
        return false;
    }
    // camera process
    auto root = doc.RootElement();

    auto xmlcamera = root;
    // auto xmlcamera = doc.FirstChildElement("camera");
    auto eye = xmlcamera->FirstChildElement("eye");
    auto lookat = xmlcamera->FirstChildElement("lookat");
    auto up = xmlcamera->FirstChildElement("up");

    camera = Camera(
        xmlcamera->Attribute("type"), xmlcamera->IntAttribute("width"), xmlcamera->IntAttribute("height"), xmlcamera->FloatAttribute("fovy"),
        eye->FloatAttribute("x"), eye->FloatAttribute("y"), eye->FloatAttribute("z"),
        lookat->FloatAttribute("x"), lookat->FloatAttribute("y"), lookat->FloatAttribute("z"),
        up->FloatAttribute("x"), up->FloatAttribute("y"), up->FloatAttribute("z"));

    // light process the elem in doc

    for (auto elem = root->NextSiblingElement(); elem != nullptr; elem = elem->NextSiblingElement())
    {
        if (std::string(elem->Name()) == "light")
        {
            auto mtlname = elem->Attribute("mtlname");
            auto radiancestr = elem->Attribute("radiance");
            // cmp with the materials loaded in obj file
            int _start = 0, _end = materials.size();
            for (; _start != _end; _start++)
            {
                if (materials[_start].name == mtlname)
                {
                    // match radiance with material id
                    is_light[_start] = 1;
                    float x, y, z;
                    sscanf(radiancestr, "%f,%f,%f", &x, &y, &z);
                    radiance[_start] = vec3(x, y, z);
                    break;
                }
            }
            if (_start == _end)
            {
                throw std::logic_error("unmatched light with material");
                return false;
            }
        }
        else
        {
            throw std::logic_error("elem unexpected");
            return false;
        }
    }
    return true;
}

void Scene::buildBVH()
{
    // initial triangles;
    for (size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;

        // Loop through each face in the shape
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Only consider triangles
            Triangle triangle;
            if (fv != 3)
                throw std::runtime_error("not tri occur in BuildBVH");
            // Loop through each vertex in the face
            for (size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                // Fill in vertex position
                float vx = attrib.vertices[3 * idx.vertex_index + 0];
                float vy = attrib.vertices[3 * idx.vertex_index + 1];
                float vz = attrib.vertices[3 * idx.vertex_index + 2];
                triangle.vertices[v] = vec3(vx, vy, vz);

                // Fill in vertex normal
                float nx = attrib.normals[3 * idx.normal_index + 0];
                float ny = attrib.normals[3 * idx.normal_index + 1];
                float nz = attrib.normals[3 * idx.normal_index + 2];
                triangle.normals[v] = vec3(nx, ny, nz);

                // Fill in vertex texture coordinates
                if (idx.texcoord_index >= 0)
                {
                    float tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                    float ty = attrib.texcoords[2 * idx.texcoord_index + 1];
                    triangle.texs[v] = vec2(tx, ty);
                }
            }

            // Set material index for the triangle
            // Set material index for the triangle
            triangle.mtlindex = shapes[s].mesh.material_ids[f];
            triangles.push_back(triangle);

            // if is light,add to lightsource
            if (is_light[triangle.mtlindex])
            {
                lights.push_back(Light(triangle, radiance[triangle.mtlindex]));
            }
            index_offset += fv;
        }
    }

    root = new BVHNode(triangles, 0, triangles.size());
}
bool Scene::intersect(const Ray &ray, const float tmin, const float tmax, hitrecord &rec)
{
    return root->intersect(ray, tmin, tmax, rec);
}

void Scene::InitLightSources()
{
    int light_id = 0;
    for (auto &light : lights)
    {
        int id = light.tri.mtlindex;
        Lightsources[id].totalarea += light.area;
        Lightsources[id].lightsid.push_back(light_id);
        ++light_id;
        if (Lightsources[id].areavec.empty())
            Lightsources[id].areavec.push_back(light.area);
        else
            Lightsources[id].areavec.push_back(light.area + Lightsources[id].areavec.back());
    }
}