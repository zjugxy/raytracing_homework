#include <iostream>
#include <vector>
#include <string>
#include <scene.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <omp.h>
const int sample_per_pixels = 400;
const float infinity = 99999999.0;
const float cut_prob = 0.7;
const float pdf = 1 / (2 * 3.14159);
const int recursiondepth = 10;

void debug(std::string str)
{
    float debug;
    std::cout << "debug " << str << std::endl;
    std::cin >> debug;
}

void teststb()
{
    const int width = 800;
    const int height = 800;
    const int channels = 3;
    std::vector<unsigned char> image(width * height * channels);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const int index = (y * width + x) * channels;
            image[index + 0] = static_cast<unsigned char>(float(x) / width * 255);
            image[index + 1] = static_cast<unsigned char>(float(y) / height * 255);
            image[index + 2] = 0;
        }
    }

    stbi_write_png("../gradient.png", width, height, channels, image.data(), width * channels);
}

void testBVH()
{
    vec3 samenorm(0, 0, 0);
    vec2 sametex(0, 0);
    int sameid = 0;
    vec3 tri1[3] = {vec3(0, 0, 0), vec3(1, 1, 1), vec3(2, 0, 0)};
    vec3 tri2[3] = {vec3(2, 2, 2), vec3(3, 2, 2), vec3(7, 2, 3)};
    vec3 tri3[3] = {vec3(5, 2, 2), vec3(6, 2, 2), vec3(6, 2, 8)};

    std::vector<Triangle> tris;
    tris.push_back(Triangle(tri1[0], tri1[1], tri1[2], samenorm, samenorm, samenorm, sametex, sametex, sametex, sameid));
    tris.push_back(Triangle(tri2[0], tri2[1], tri2[2], samenorm, samenorm, samenorm, sametex, sametex, sametex, sameid));
    tris.push_back(Triangle(tri3[0], tri3[1], tri3[2], samenorm, samenorm, samenorm, sametex, sametex, sametex, sameid));
    auto root = new BVHNode(tris, 0, tris.size());

    vec3 ori(1, 0.5, 0);
    vec3 dir(0, 0, 1);
    Ray r(ori, dir);
    hitrecord rec;
    if (root->intersect(r, 0, 999999, rec))
    {
        std::cout << "hit" << std::endl;
    }
}

vec3 ray_color(Scene &scene, Ray &ray, int depth)
{
    hitrecord rec;
    if (depth <= 0 || (scene.intersect(ray, 0, infinity, rec) == false))
    {
        return vec3(0, 0, 0);
    }
    // get random num
    float num = random_float();
    if (num > cut_prob)
        return vec3{0, 0, 0};
    // 本该是light的id失效了 变成了0
    int id = rec.materialid;
    // hit light
    if (scene.is_light[id])
    {
        return scene.radiance[id] * float((1.0 / cut_prob));
    }

    vec3 albedo;
    Ray newray;
    if (scene.mymaterials[id]->scatter(ray, rec, albedo, newray))
    {
        vec3 wo = float(-1.0) * ray.dir;
        vec3 wi = newray.dir;
        float elem = 1 / pdf / cut_prob;
        //        return fr(p, wi, wo) * shade(o, -wi) * dot(n, wi) / pdf(wi) / prob;
        return albedo * glm::dot(rec.normal, wi) * ray_color(scene, newray, depth - 1) * elem;
    }
}

// add direct light
vec3 ray_color_direct(Scene &scene, Ray &ray, int depth)
{
    // recursion end or hit nothing
    hitrecord rec;
    if (depth <= 0 || (scene.intersect(ray, 0, infinity, rec) == false))
    {
        return vec3(0, 0, 0);
    }
    // hit something,need to calculate the light on that point
    // sample light
    vec3 hitpostion = rec.position;
    int id = rec.materialid;
    vec3 recnorm = glm::normalize(rec.normal);
    vec3 diffuseelem = scene.mymaterials[id]->lightelem();
    // 光源效果只由L_dir计算
    // 只会在初次发射光线碰到光源时生效
    if (scene.is_light[id])
    {
        if (depth == recursiondepth)
            return scene.radiance[id];
        else
            return vec3(0, 0, 0);
    }

    vec3 L_dir(0, 0, 0);
    for (auto &light : scene.lightsources)
    {
        // sample a point (u,v,1-u-v)
        vec3 samplepoint = sample_tri();
        vec3 position, normal;
        if (!light.tri.calculate_fromuv(samplepoint, position, normal))
            std::cout << "error in light";
        // check if ray can hit light
        vec3 dir = glm::normalize(position - hitpostion);
        Ray testray(hitpostion, dir);
        float truelength = glm::length(position - hitpostion);
        hitrecord testrec;
        scene.intersect(testray, 0, infinity, testrec);
        // 中间无遮挡物
        if (testrec.t > (truelength - 0.001))
        {
            float elem = glm::dot(recnorm, dir) * glm::dot(-1.0f * dir, glm::normalize(normal));
            elem /= truelength * truelength;
            elem *= light.area;
            L_dir += light.radiance * diffuseelem * elem;
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
        if (scene.mymaterials[id]->scatter(ray, rec, albedo, newray))
        {
            vec3 wo = float(-1.0) * ray.dir;
            vec3 wi = newray.dir;
            float elem = 1 / pdf / cut_prob;
            return albedo * glm::dot(recnorm, wi) * ray_color_direct(scene, newray, depth - 1) * elem;
        }
    }
    return L_dir + L_indir;
}

vec3 Shader(Scene &scene, hitrecord rec, Ray &ray_in)
{
    //
    vec3 hitpostion = rec.position;
    int id = rec.materialid;
    vec3 recnorm = glm::normalize(rec.normal);

    // 光源效果只由L_dir计算
    // 只会在初次发射光线碰到光源时生效
    vec3 L_dir(0, 0, 0);
    for (auto &light : scene.lightsources)
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
        if(std::abs(testrec.t-truelength)<0.001)
        {
            float elem = glm::dot(recnorm, dir_out) * glm::dot(-1.0f * dir_out, glm::normalize(normal));
            elem /= truelength * truelength;
            elem *= light.area;
            L_dir += light.radiance * scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, dir_out) * elem;
            // Li * f_r *cos *cos /length**2 / pdf
        }
        else
        {
            L_dir += vec3(0, 0, 0);
        }
    }

    vec3 L_indir(0, 0, 0);
    // float num = random_float();
    // if (num > cut_prob)
    // {
    //     L_indir = vec3{0, 0, 0};
    // }
    // else
    // {
    //     // trace a ray
    //     Ray newray;
    //     vec3 albedo;
    //     scene.mymaterials[id]->scatter(ray_in, rec, albedo, newray);
    //     hitrecord newrec;
    //     if (!scene.intersect(newray, 0, infinity, newrec)) // 没打中任何物体
    //         L_indir = vec3(0, 0, 0);
    //     else if (scene.is_light[newrec.materialid]) // 打中了光
    //         L_indir = vec3(0, 0, 0);
    //     else
    //     {
    //         float elem = glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
    //         L_indir = Shader(scene, newrec, newray) * scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, newray.dir) * elem;
    //     }
    // }
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
        scene.mymaterials[id]->scatter(ray_in, rec, albedo, newray);
        hitrecord newrec;
        if (!scene.intersect(newray, 0, infinity, newrec)) // 没打中任何物体
            L_indir = vec3(0, 0, 0);
        else if (scene.is_light[newrec.materialid]) // 打中了光
            L_indir = scene.radiance[newrec.materialid]*scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, newray.dir)*
            glm::dot(recnorm, glm::normalize(newray.dir))/pdf/cut_prob;
        else
        {
            float elem = glm::dot(recnorm, glm::normalize(newray.dir)) / pdf / cut_prob;
            L_indir = newshader(scene, newrec, newray) * scene.mymaterials[id]->BRDF(-1.0f * ray_in.dir, newray.dir) * elem;
        }
    }
    return  L_indir;
};

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

vec3 bygames101(Scene &scene, Ray &ray, int depth)
{
    hitrecord inter;
    if (!scene.intersect(ray, 0, infinity, inter) || depth < 0)
    {
        return vec3(0, 0, 0);
    }
    int id = inter.materialid;
    vec3 recnorm = glm::normalize(inter.normal);
    vec3 hitpostion = inter.position;
    if (scene.is_light[id])
        return scene.radiance[id];

    vec3 L_dir(0, 0, 0), L_indir(0, 0, 0);
    for (auto &light : scene.lightsources)
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
        if (testrec.t > (truelength - 0.001))
        {
            float elem = glm::dot(recnorm, dir_out) * glm::dot(-1.0f * dir_out, glm::normalize(normal));
            elem /= truelength * truelength;
            elem *= light.area;
            L_dir += light.radiance * scene.mymaterials[id]->BRDF(-1.0f * ray.dir, dir_out) * elem;
            // Li * f_r *cos *cos /length**2 / pdf
        }
        else
        {
            L_dir += vec3(0, 0, 0);
        }
    }
    if (random_float() < cut_prob)
    {
        Ray newray;
        vec3 albo;
        scene.mymaterials[id]->scatter(ray, inter, albo, newray);
        hitrecord newrec;
        if (scene.intersect(newray, 0, infinity, newrec) && scene.is_light[newrec.materialid] == false)
        {
            L_indir = bygames101(scene, newray, depth - 1) * scene.mymaterials[id]->BRDF(-1.f * ray.dir, newray.dir) * glm::dot(glm::normalize(newray.dir), recnorm) / pdf / cut_prob;
        }
    }
    return L_dir + L_indir;
}



int main()
{
    Scene myscene;

    const char *filename = "../example/cornell-box/cornell-box.obj";
    const char *basefile = "../example/cornell-box/"; // used to find mtl file
    const char *xmlfile = "../example/cornell-box/cornell-box.xml";
    // load obj first to match the material with xml file
    myscene.loadobj(filename, basefile);
    myscene.loadxml(xmlfile);
    myscene.buildBVH();
    std::cout << "num of light tris " << myscene.lightsources.size() << std::endl;
    std::cout << "total triangles" << myscene.triangles.size() << std::endl;

    // testAABB();
    // testBVH();
    // teststb();

    const int width = myscene.camera.width;
    const int height = myscene.camera.height;
    const int channels = 3;
    int depth = recursiondepth;
    std::vector<unsigned char> image(width * height * channels);

    int debugheight = 767; // 开始调试第128行,适用于1024分辨率
    int debugx = 113;
    // 原先      for (int y = height-1; y >= 0; --y) {

    //#pragma omp parallel for
    for (int y = debugheight; y >= 0; --y)
    {
        std::cout << "line in" << y << std::endl;
        // 原先      for (int x = 0; x < width; ++x) {
        for (int x = debugx; x < width; ++x)
        {

            // std::cout<<"error in "<<x<<std::endl;
            int index = (((height - 1) - y) * width + x) * 3;
            vec3 color{0, 0, 0};
            Ray r = myscene.camera.castray(float(x) / width, float(y) / height);
            for (int k = 0; k < sample_per_pixels; k++)
            {
                color += ray_color_from_camera(myscene, r);
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
    stbi_write_png("../cornell.png", width, height, channels, image.data(), width * channels);

    return 0;
}
