#pragma once 

namespace functions {
    void rebase();
    void update_pointers();
    const char* va(const char* str, ...);

    namespace client {
        bool is_me(structs::player* client);
        bool is_friend(structs::player* client);
        bool is_alive(structs::player* client);
        bool world_to_screen(const math::vec3& world, math::vec3& screen);
        bool is_visible(const math::vec3& start, const math::vec3& end); 
    }

    namespace engine {
        float ray_cube(const math::vec3* from , const math::vec3* ray, float max_dist, uint32_t mode, uint32_t size, void* ent);
    }

    namespace sdl {
        uint32_t set_relative_mouse_mode(uint32_t mode);
    }
}