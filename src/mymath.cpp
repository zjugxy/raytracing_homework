#include<mymath.h>
bool judge_equal(float elems[],float cmp)
{
    for(int i=0;i<3;i++)
        if(elems[i]!=cmp)
            return false;
    return true;
}

vec3 random_vec3(){
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // 创建一个均匀分布的实数分布器，范围为[-1, 1]
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    float x = dis(gen);
    float y = dis(gen);
    float z = dis(gen);
    return vec3(x,y,z);
}

float random_float(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

float clamp(float value,float min,float max){
    if(min>value)
        return min;
    if(max<value)
        return max;
    return value;
}

vec3 sample_tri(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    float u = dis(gen);
    float v = dis(gen);
    while(u+v>1){
        u = dis(gen);
        v = dis(gen);
    }

    return vec3(u,v,1-u-v);
}