#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;
using namespace glm;

vec3 sphToCart(const vec3& s) {
    float r = s.x;
    float theta = s.y;
    float phi = s.z;

    float x = r * sin(theta) * cos(phi);
    float y = r * sin(theta) * sin(phi);
    float z = r * cos(theta);

    return vec3(x, y, z);
}