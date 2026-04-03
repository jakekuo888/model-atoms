#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;
using namespace glm;

struct HIT {
	vec3 Q, N; //Q = pos, N = s normal
	const Sphere* M;
	bool hit;
};

class Sphere {
public:
	vec3 center;
	float rad;
	vec3 col;

	float intersect(const vec3& P, const vec3& d){
		vec3 oc = P - center;
		float a = dot(d,d);
		float b = 2.0f * dot(oc, d);
		float c = dot(oc, oc) - rad*rad;
		float disc = b*b - 4 * a * c;

		if(disc < 0)
			return -1.0f;
		float t1 = (-b - sqrt(disc)) / (2.0f * a);
        float t2 = (-b + sqrt(disc)) / (2.0f * a);
		return ((t1>0)?t1:(t2>0)?t2:-1.0f);
	}

	vec3 normal(const vec3& point) const{
		return normalize(point-center);
	}
};

class Scene {
public:
	vector<Sphere> obj;
	vec3 lPos;

	HIT intersect(const vec3& P, const vec3& d){
		float minT = numeric_limits<float>::max();
		const Sphere* hitObj = nullptr;

		for(const auto& sphere : obj){
			float t = sphere.intersect(P, d);
			if(t > 0 && t < minT){
				minT = t;
				hitObj = &sphere;
			}
		}
		if(!hitObj)
			return {vec3(0), vec3(0), nullptr, false};

		vec3 Q = P + d*minT;
		vec3 N = hitObj->normal(Q);

		return {Q, N, hitObj, true};
	}
};

class Ray {
public:
	vec3 P; //pos
	vec3 d; //dir

	vec3 traceRay(const Scene& scene){
		HIT QNM = scene.intersect(P, d);
		if(!QNM.hit)
			return vec3(0); //background col
		vec3 L = normalize(scene.lPos - hitData.Q);
		float diff = dot(QNM.N, L);
		float threshold = 0.5f;

		vec3 shadedColor   = hitData.M->col;
		vec3 unshadedColor = hitData.M->col * 0.2f;

		if(diff > threshold)
			return shadedColor;
		else
			return unshadedColor;
	}
};

class Camera {
public:
	vec3 position;
	int WIDTH, HEIGHT;
};