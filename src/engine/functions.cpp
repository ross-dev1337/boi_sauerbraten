#include "dll_main.h"
 
void functions::rebase() {
    const auto module = GetModuleHandle(nullptr);

    if (module == nullptr) {
        globals::game_base = 0;
        return;
    }

    const auto base = reinterpret_cast<uint64_t>(module);
    globals::game_base = base;
   // printf("%llx\n", globals::game_base); // 7ff726f50000
    
    
    globals::game_vars::ray_cube = base + 0x1142C0;
 
    structs::screen = reinterpret_cast<structs::screen_dimensions*>(base + 0x2A3534);
    structs::matrix = reinterpret_cast<structs::view_matrix*>(base + 0x32D040);
    update_pointers();
}

// the game can reallocate these at runtime (map change, players joining), so re-read them every frame
void functions::update_pointers() {
    const auto base = globals::game_base;
    if (base == 0)
        return;

    structs::local_player = *reinterpret_cast<structs::player**>(base + 0x2A5730);
    structs::ent = *reinterpret_cast<structs::entity**>(base + 0x346C90);
    globals::game_vars::player_count = *reinterpret_cast<uint32_t*>(base + 0x346C9C);
}


bool functions::client::is_me(structs::player* client) {
    return client == structs::local_player;
}

bool functions::client::is_friend(structs::player* client) {
    return client->team[0] != '\0' && !strcmp(client->team, structs::local_player->team);
}

bool functions::client::is_alive(structs::player* client) {
    return client->state == 0;  
}

bool functions::client::world_to_screen(const math::vec3& world, math::vec3& screen) {
    const auto& matrix = structs::matrix->view;

    const float clip_x = world.x * matrix[0] + world.y * matrix[4] + world.z * matrix[8] + matrix[12];

    const float clip_y = world.x * matrix[1] + world.y * matrix[5] + world.z * matrix[9] + matrix[13];

    const float clip_w = world.x * matrix[3] + world.y * matrix[7] + world.z * matrix[11] + matrix[15];

    if (clip_w <= 0.1f)
        return false;

    const float inv_w = 1.0f / clip_w;

    const float ndc_x = clip_x * inv_w;
    const float ndc_y = clip_y * inv_w;

    const float half_width = structs::screen->width * 0.5f;
    const float half_height = structs::screen->height * 0.5f;

    screen.x = half_width + ndc_x * half_width;
    screen.y = half_height - ndc_y * half_height;

    return true;
}

bool functions::client::is_visible(const math::vec3& start, const math::vec3& end) {
    const math::vec3 delta = end - start;
    const float dist = ::sqrtf(delta.dot(delta)); 

    if(dist <= 0.f)
        return true; 

    const math::vec3 dirction = delta * (1.f / dist); // raycube wants a normalized direction, not an end point
    constexpr uint32_t ray_clipmat_alphapoly = 16 | 7; // same mode shoot() uses

    const float barrier = engine::ray_cube(&start, &dirction, dist, ray_clipmat_alphapoly, 0, nullptr);

    return !(barrier > 0.f && barrier < dist - .1f); 
}

float functions::engine::ray_cube(const math::vec3* from , const math::vec3* ray, float max_dist, uint32_t mode, uint32_t size, void* ent) {
    return call<float>(globals::game_vars::ray_cube, from, ray, max_dist, mode, size, ent); 
}

const char* functions::va(const char* str, ...) {
    thread_local std::array<char, 512> buffer{};

    va_list args;
    va_start(args, str);
    ::vsnprintf(buffer.data(), buffer.size(), str, args);
    va_end(args);

    return buffer.data();
}

uint32_t functions::sdl::set_relative_mouse_mode(uint32_t mode) {
    return call<uint32_t>(globals::mouse_move, mode);
}