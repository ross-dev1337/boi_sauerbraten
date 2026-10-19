#pragma once
 
template <typename T, typename... Args>
static T call(std::uintptr_t address, Args... args) {
	auto fn = reinterpret_cast<T (*)(Args...)>(address);
	return fn(args...);
}

namespace math {

	struct vec3 {
		float x{}, y{}, z{};

		constexpr vec3() = default;

		constexpr vec3(float x, float y, float z)
			: x(x), y(y), z(z) {}

		vec3 operator+(const vec3 &v) const {
			return vec3(x + v.x, y + v.y, z + v.z);
		}

		vec3 operator-(const vec3 &v) const {
			return vec3(x - v.x, y - v.y, z - v.z);
		}

		vec3 operator*(const vec3 &v) const {
			return vec3(x * v.x, y * v.y, z * v.z);
		}

		// scale
		vec3 operator*(float s) const {
			return {x * s, y * s, z * s};
		}

		float distance(const vec3 v) const {
			float dis_x = x - v.x, dis_y = y - v.y, dis_z = z - v.z;
			return sqrt((dis_x * dis_x) + (dis_y * dis_y) + (dis_z * dis_z) * 1.f);
		}

		float dot(const vec3 &v) const {
			return (x * v.x) + (y * v.y) + (z * v.z);
		}
	};

	struct vec2 {
		float x{}, y{};

		constexpr vec2() = default;

		constexpr vec2(float x, float y)
			: x(x), y(y) {}
	};

	struct matrix4x4 {
		float matrix[16];

		float &operator[](std::size_t i) {
			return matrix[i];
		}

		const float &operator[](std::size_t i) const {
			return matrix[i];
		}
	};
};

namespace structs {

    // <sauerbraten.exe>+0x2A5730
	 struct player {
        math::vec3 origin1; //0x0000
	    char _0x000C[0x24]; //0x000C
	    math::vec3 origin2; //0x0030
	    math::vec3 view_angles; //0x003C
	    char _0x0048[0x130]; //0x0048
	    uint32_t current_health; //0x0178
	    uint32_t max_health; //0x017C
	    uint32_t armor; //0x0180
	    char _0x0184[0xF0]; //0x0184
        char name[15]; // 0x0274
        char _0x0283[0xF5]; // 0x0283
        char team[4]; // 0x0378
     }; 
     inline player* local_player; 

	 // <sauerbraten.exe>+0x346C90
	 struct entity {
		player* entites[32];
	 };
	 inline entity* ent; 


     struct screen_dimensions {
        uint32_t height; 
        uint32_t width; 
     }; 
     inline screen_dimensions* screen; 

	 struct view_matrix {
		math::matrix4x4 view; 
	 }; 
	 inline view_matrix* matrix; 
};