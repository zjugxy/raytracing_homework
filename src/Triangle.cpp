#include<Triangle.h>
    Triangle::Triangle(const vec3& v0, const vec3& v1, const vec3& v2,const vec3& n0, const vec3& n1, const vec3& n2,
    const vec2& t0, const vec2& t1, const vec2& t2,size_t index)
        : vertices{ v0, v1, v2 },normals{n0,n1,n2},texs{t0,t1,t2},mtlindex(index)
    {
    }

    AABB Triangle::get_bbox()const{ 
        return AABB(vertices[0],vertices[1],vertices[2]);
    }

    bool Triangle::intersect(const Ray& ray,double t_min,double t_max,hitrecord& rec)const{

    vec3 e1 = vertices[1] - vertices[0];
    vec3 e2 = vertices[2] - vertices[0];
    vec3 pvec = glm::cross(ray.direction(), e2);
    double det = glm::dot(e1, pvec);

    // If det is close to 0, the ray and triangle are parallel.
    if (fabs(det) < 1e-8) {
        return false;
    }

    double inv_det = 1.0 / det;
    vec3 tvec = ray.origin() - vertices[0];
    double u = glm::dot(tvec, pvec) * inv_det;

    if (u < 0.0 || u > 1.0) {
        return false;
    }

    vec3 qvec = glm::cross(tvec, e1);
    double v = glm::dot(ray.direction(), qvec) * inv_det;

    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    double t = glm::dot(e2, qvec) * inv_det;

    if (t <= t_min || t >= t_max) {
        return false;
    }

    if (t < rec.t) {
        rec.t = t;
        rec.position = ray.at(t);
        rec.normal = glm::normalize(float((1 - u - v)) * normals[0] + float(u) * normals[1] + float(v) * normals[2]);
        rec.materialid = mtlindex;
    }
    else {
        return false;
    }
    return true;
}

    bool Triangle::calculate_fromuv(const vec3& coord,vec3& position,vec3& normal)const{
        float x=coord[0],y = coord[1],z=coord[2];
        if(x<0||y<0||z<0||(x+y+z)>1)
            return false;
        position = vertices[0]*x+vertices[1]*y+vertices[2]*z;
        normal = normals[0]*x+normals[1]*y+normals[2]*z;
        return true;
    };