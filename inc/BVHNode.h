#pragma once
#include "AABB.h"
#include <Triangle.h>
#include<vector>
#include<algorithm>
#include<hitreord.h>

class BVHNode {
public:
    BVHNode( std::vector<Triangle>& triangles, int start, int end)
        : left(nullptr), right(nullptr) {
        // Compute the bounding box for all triangles in the range [start, end).

        for (int i = start; i < end; i++) {
            bbox.MergePoint(triangles[i].vertices[0]);
            bbox.MergePoint(triangles[i].vertices[1]);
            bbox.MergePoint(triangles[i].vertices[2]);
        }

        // If there is only one triangle in the range, make this node a leaf.
        triptr = &triangles;
        if (end - start == 1) {
            leaf = true;
            leaf_index = start;
        }
        // Otherwise, split the range and recursively build the left and right subtrees.
        else {
            leaf = false;
            int axis = bbox.get_longest_axis();
            int mid = (start + end) / 2;

            std::nth_element(triangles.begin() + start, triangles.begin() + mid, triangles.begin() + end, 
                [&](const Triangle& t1, const Triangle& t2) {
                    return t1.get_bbox().get_centroid()[axis] < t2.get_bbox().get_centroid()[axis];
                });
            if(mid>start)
                left = new BVHNode(triangles, start, mid);
            if(end>mid)
                right = new BVHNode(triangles, mid, end);
        }
    }

    ~BVHNode() {
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }

    const AABB& get_bbox() const {
        return bbox;
    }

    bool intersect(const Ray& ray, float t_min, float t_max, hitrecord& rec) const {
        if (!bbox.intersect(ray, t_min, t_max)) {
            return false;
        }

        if (leaf) {
            return (*triptr)[leaf_index].intersect(ray, t_min, t_max, rec);
        }

        bool hit_left = (left==nullptr)?false:left->intersect(ray, t_min, t_max, rec);
        bool hit_right = (right==nullptr)?false:right->intersect(ray, t_min, t_max, rec);
        return hit_left || hit_right;
    }

public:
    AABB bbox;
    bool leaf;
    int leaf_index;
    std::vector<Triangle>* triptr;
    BVHNode* left;
    BVHNode* right;

    //test uesd argu
    int teststart;
    int testend;
};