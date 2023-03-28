#include <mymath.h>
bool judge_equal(float elems[], float cmp)
{
    for (int i = 0; i < 3; i++)
        if (elems[i] != cmp)
            return false;
    return true;
}

vec3 random_vec3()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    while (true)
    {
        float x = dis(gen);
        float y = dis(gen);
        float z = dis(gen);
        
        vec3 ret(x, y, z);
        if(glm::length(ret)<1.0)
            return ret;
    }
    

}

float random_float()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

float clamp(float value, float min, float max)
{
    if (min > value)
        return min;
    if (max < value)
        return max;
    return value;
}

vec3 sample_tri()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0001, 0.9999);

    float u = dis(gen);
    float v = dis(gen);

    return vec3(std::sqrt(v)*(1-u), u*std::sqrt(v), 1 - std::sqrt(v));
}