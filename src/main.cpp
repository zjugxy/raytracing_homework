#include <iostream>
#include <vector>
#include <string>
#include <scene.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <omp.h>
const int sample_per_pixels = 100;
const float infinity = 99999999.0;
const float cut_prob = 0.7;

const int recursiondepth = 10;

void debug(std::string str)
{
    float debug;
    std::cout << "debug " << str << std::endl;
    std::cin >> debug;
}

// vec3 ray_color(Scene &scene, Ray &ray, int depth)
// {
//     hitrecord rec;
//     if (depth <= 0 || (scene.intersect(ray, 0, infinity, rec) == false))
//     {
//         return vec3(0, 0, 0);
//     }
//     // get random num
//     float num = random_float();
//     if (num > cut_prob)
//         return vec3{0, 0, 0};
//     // 本该是light的id失效了 变成了0
//     int id = rec.materialid;
//     // hit light
//     if (scene.is_light[id])
//     {
//         return scene.radiance[id];
//     }

//     vec3 albedo;
//     Ray newray;
//     if (scene.mymaterials[id]->scatter(ray, rec, albedo, newray))
//     {
//         vec3 wo = float(-1.0) * ray.dir;
//         vec3 wi = newray.dir;
//         float elem = 1 / pdf / cut_prob;
//         //        return fr(p, wi, wo) * shade(o, -wi) * dot(n, wi) / pdf(wi) / prob;
//         return scene.mymaterials[id]->BRDF(wi,wo,rec) * glm::dot(rec.normal, wi) * ray_color(scene, newray, depth - 1) * elem;
//     }
// }

vec3 Shader(Scene &scene, hitrecord rec, Ray &ray_in)
{
    //
    vec3 hitpostion = rec.position;
    int id = rec.materialid;
    vec3 recnorm = glm::normalize(rec.normal);

    // 光源效果只由L_dir计算
    // 只会在初次发射光线碰到光源时生效
    vec3 L_dir(0, 0, 0);
    // 光源三角形少的时候好用
    for (auto &light : scene.lights)
    {
        // sample a point (u,v,1-u-v)
        vec3 samplepoint = sample_tri();
        vec3 position, normal;
        if (!light.tri.calculate_fromuv(samplepoint, position, normal))
            std::cout << "error in light";
        // check if ray can hit light
        vec3 dir_out = glm::normalize(position - hitpostion);
        Ray testray(hitpostion, dir_out);
        float truelength = glm::length(position - hitpostion);
        hitrecord testrec;
        scene.intersect(testray, 0, infinity, testrec);
        // 中间无遮挡物
        if (std::abs(testrec.t - truelength) < 0.001)
        {
            float elem = glm::dot(recnorm, dir_out) * glm::dot(-1.0f * dir_out, glm::normalize(normal));
            elem /= truelength * truelength;
            elem *= light.area;
            L_dir += light.radiance * scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, dir_out, testrec) * elem;
            // Li * f_r *cos *cos /length**2 / pdf
        }
        else
        {
            L_dir += vec3(0, 0, 0);
        }
    }

    vec3 L_indir(0, 0, 0);
    float num = random_float();
    if (num > cut_prob)
    {
        L_indir = vec3{0, 0, 0};
    }
    else
    {
        // trace a ray
        Ray newray;
        vec3 albedo;
        float pdf;
        scene.mymaterials[id]->scatter(ray_in, rec, albedo, newray, pdf);
        hitrecord newrec;
        if (!scene.intersect(newray, 0, infinity, newrec)) // 没打中任何物体
            L_indir = vec3(0, 0, 0);
        else if (scene.is_light[newrec.materialid]) // 打中了光
            L_indir = vec3(0, 0, 0);
        else
        {
            float elem = glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
            L_indir = Shader(scene, newrec, newray) * scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, newray.dir, newrec) * elem;
        }
    }
    return L_dir + L_indir;
};

vec3 newshader(Scene &scene, hitrecord rec, Ray &ray_in)
{
    //
    vec3 hitpostion = rec.position;
    int id = rec.materialid;
    vec3 recnorm = glm::normalize(rec.normal);

    // 光源效果只由L_dir计算
    // 只会在初次发射光线碰到光源时生效
    vec3 L_dir(0, 0, 0);

    vec3 L_indir(0, 0, 0);
    float num = random_float();
    if (num > cut_prob)
    {
        L_indir = vec3{0, 0, 0};
    }
    else
    {
        // trace a ray
        Ray newray;
        vec3 albedo;
        float pdf;
        scene.mymaterials[id]->scatter(ray_in, rec, albedo, newray, pdf);
        hitrecord newrec;
        if (!scene.intersect(newray, 0, infinity, newrec)) // 没打中任何物体
            L_indir = vec3(0, 0, 0);
        else if (scene.is_light[newrec.materialid]) // 打中了光
            L_indir = scene.radiance[newrec.materialid] * albedo * glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
        else
        {
            float elem = glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
            L_indir = newshader(scene, newrec, newray) * albedo * elem;
        }
    }
    return L_indir;
};

// 重要性采样的实现没有太大问题，但是reflectance的BRDF实现有不少问题
vec3 multisampleshader(Scene &scene, hitrecord rec, Ray &ray_in)
{

    vec3 hitposition = rec.position;
    vec3 recnorm = glm::normalize(rec.normal);
    int id = rec.materialid;
    vec3 w_o = -1.0f * glm::normalize(ray_in.dir);
    vec3 L(0.0f, 0.0f, 0.0f);

    float randelem = random_float();
    if (randelem > cut_prob)
        return vec3(0.0f, 0.0f, 0.0f);

    for (auto &lightsourcepair : scene.Lightsources)
    {
        int radianceid = lightsourcepair.first;
        auto lightsource = lightsourcepair.second;
        int lightid = lightsource.SampleLight();

        Light light = scene.lights[lightid];
        vec3 samplepoint = sample_tri();
        vec3 position, normal;
        if (!light.tri.calculate_fromuv(samplepoint, position, normal))
            std::cout << "error in light";

        vec3 dir_out = glm::normalize(position - hitposition);
        Ray testray(hitposition, dir_out);
        float truelength = glm::length(position - hitposition);
        hitrecord testrec;
        scene.intersect(testray, 0, infinity, testrec);

        if (std::abs(testrec.t - truelength) < 0.001)
        {
            // PDF,L_DIR
            float PDF = 1.0f / lightsource.totalarea;
            float elem = glm::dot(recnorm, dir_out) * glm::dot(-1.0f * dir_out, glm::normalize(normal));
            elem /= truelength * truelength;

            vec3 L_dir = light.radiance * scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, dir_out, testrec) * elem / PDF / cut_prob;
            float PDF2 = scene.mymaterials[id]->MTLPDF(dir_out, w_o, rec);
            float weight = powerweight(PDF, PDF2);

            L += L_dir * weight;
        }
        else
        {
            continue;
        }
    }

    // trace a ray
    Ray newray;
    vec3 albedo;
    float pdf;
    vec3 L_indir;
    scene.mymaterials[id]->scatter(ray_in, rec, albedo, newray, pdf);
    hitrecord newrec;
    if (!scene.intersect(newray, 0, infinity, newrec)) // 没打中任何物体
        L_indir = vec3(0, 0, 0);
    else if (scene.is_light[newrec.materialid]) // 打中了光
    {
        L_indir = scene.radiance[newrec.materialid] * albedo * glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
        float lightsourceid = newrec.materialid;
        float area = scene.Lightsources[lightsourceid].totalarea;
        float PDF2 = 1 / area;
        float weight = powerweight(pdf, PDF2);
        L_indir *= weight;
    }
    else
    {
        float elem = glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
        L_indir = newshader(scene, newrec, newray) * albedo * elem;
    }

    return L + L_indir;
}

vec3 ray_color_from_camera(Scene &scene, Ray ray)
{
    hitrecord rec;
    if (!scene.intersect(ray, 0, infinity, rec))
        return vec3(0, 0, 0);
    int id = rec.materialid;
    if (scene.is_light[id]) // 直接打到光源上面
        return scene.radiance[id];
    else
    {
        return Shader(scene, rec, ray);
    }
}

vec3 ray_color_from_camera_new(Scene &scene, Ray ray)
{
    hitrecord rec;
    if (!scene.intersect(ray, 0, infinity, rec))
        return vec3(0, 0, 0);
    int id = rec.materialid;
    if (scene.is_light[id]) // 直接打到光源上面
        return scene.radiance[id];
    else
    {
        return newshader(scene, rec, ray);
    }
}

vec3 ray_color_from_malti(Scene &scene, Ray ray)
{
    hitrecord rec;
    if (!scene.intersect(ray, 0, infinity, rec))
        return vec3(0, 0, 0);
    int id = rec.materialid;
    if (scene.is_light[id]) // 直接打到光源上面
        return scene.radiance[id];
    else
    {
        return multisampleshader(scene, rec, ray);
    }
}

int main()
{
    Scene myscene;

    // const char *filename = "../example/veach-mis/veach-mis.obj";
    // const char *basefile = "../example/veach-mis/"; // used to find mtl file
    // const char *xmlfile = "../example/veach-mis/veach-mis.xml";

    const char *filename = "../example/staircase/stairscase.obj";
    const char *basefile = "../example/staircase/"; // used to find mtl file
    const char *xmlfile = "../example/staircase/staircase.xml";


    // load obj first to match the material with xml file
    myscene.loadobj(filename, basefile);
    myscene.loadxml(xmlfile);
    myscene.buildBVH();
    myscene.InitLightSources();
    std::cout << "num of light tris " << myscene.lights.size() << std::endl;
    std::cout << "total triangles" << myscene.triangles.size() << std::endl;
    std::cout << "num of light sources" << myscene.Lightsources.size() << std::endl;

    const int width = myscene.camera.width;
    const int height = myscene.camera.height;
    const int channels = 3;
    int depth = recursiondepth;
    std::vector<unsigned char> image(width * height * channels);

    int debugheight = 767; // 开始调试第128行,适用于1024分辨率
    int debugx = 113;
    // 原先      for (int y = height-1; y >= 0; --y) {

    #pragma omp parallel for
    for (int y = height - 1; y >= 0; --y)
    {
        std::cout << "line in" << y << std::endl;
        // 原先      for (int x = 0; x < width; ++x) {
        for (int x = 0; x < width; ++x)
        {

            // std::cout<<"error in "<<x<<std::endl;
            int index = (((height - 1) - y) * width + x) * 3;
            vec3 color{0, 0, 0};
            Ray r = myscene.camera.castray(float(x) / width, float(y) / height);
            // std::cout<<"debug x in ************"<<x<<std::endl;
            for (int k = 0; k < sample_per_pixels; k++)
            {
                color += ray_color_from_camera_new(myscene, r);
            }
            color /= float(sample_per_pixels);
            float R = clamp(color[0], 0.0, 0.999) * 255;
            float G = clamp(color[1], 0.0, 0.999) * 255;
            float B = clamp(color[2], 0.0, 0.999) * 255;
            image[index + 0] = static_cast<unsigned char>(R);
            image[index + 1] = static_cast<unsigned char>(G);
            image[index + 2] = static_cast<unsigned char>(B);
        }
    }
    stbi_write_png("../veach.png", width, height, channels, image.data(), width * channels);

    return 0;
}
