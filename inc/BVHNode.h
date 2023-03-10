#pragma once
#include<AABB.h>

class BVHNode{
    public:
    AABB aabb;
    BVHNode* left;
    BVHNode* right;
    BVHNode();    
};

class TriNode:public BVHNode{
    
}
