#pragma once 
 
namespace aimbot {
    inline structs::player* current_target = nullptr; 

    structs::player* closest_client(); 
    void vec_to_angles(const math::vec3& vec, math::vec3& angles);
    void do_aimbot(); 
}