#pragma once

#include <array>
#include <cstdlib>

namespace math {

	// vectors
	struct vec2{
		vec2(float val);
		vec2(float x, float y);
		vec2();
		float x, y;

		vec2 operator+(const vec2& vec){
			return vec2(x + vec.x, y + vec.y);	
		}

		vec2 operator+(float val){
			return vec2(x + val, y + val);	
		}

		vec2 operator-(const vec2& vec){
			return vec2(x - vec.x, y - vec.y);	
		}

		vec2 operator-(float val){
			return vec2(x - val, y - val);	
		}

		vec2 operator*(const vec2& vec){
			return vec2(x * vec.x, y * vec.y);	
		}

		vec2 operator*(float val){
			return vec2(x * val, y * val);
		}
	};

	struct vec3{
		vec3(float val);
		vec3();
	};

	struct vec4 {
		vec4(float val);
		vec4();
		float v[4];
	};

    // matrices
	struct mat4 {
		mat4(float n); // inits all values to param f
		float m[4][4];
	};

	// functions
	mat4 perspective(float fovy, float aspect, float zNear, float zFar);

	// returns float with specified decimals
	float round(double f, size_t decimals);

};