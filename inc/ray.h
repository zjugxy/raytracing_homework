#pragma once
#include <mymath.h>

class Ray{
    private:
    Point _origin;
    Dir _dir;
    public:
    Ray(Point origin,Dir dir):_origin(origin),_dir(dir){}
    Ray(){}
    Point origin(){return _origin;}
    Dir dir(){return _dir;}
    Point At(float t){
        return _origin+_dir*t;
    }
};