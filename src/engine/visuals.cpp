#include "dll_main.h"
  
void visuals::opengl::draw_rect(float x, float y, float width, float height, ImVec4 color) {
    ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, .5f)));
    // outline
    ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), ImGui::GetColorU32(ImVec4(color)), 0.0f, 0, 1.0f);
}

void visuals::opengl::draw_string(const char* string, float x, float y, ImVec4 color) {
    ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::GetColorU32(ImVec4(color.x, color.y, color.z, color.w)), string, NULL);
}

void visuals::opengl::draw_text_shader(const char* string, float x, float y, ImVec4 color, ImVec4 color2, globals::align alignment) {
    const ImVec2 text_size = ImGui::CalcTextSize(string);

    switch (alignment) {
    case globals::align::x_center:
        x -= text_size.x * .5f;
        break;
    case globals::align::x_right:
        x -= text_size.x;
        break;
    case globals::align::x_left:
    default:
        break;
    }

    opengl::draw_rect(x - 3.f, y, text_size.x + 6.f, text_size.y, color2);
    opengl::draw_string(string, x, y, color);
}

void visuals::opengl::draw_line(float x, float y, float x2, float y2, ImVec4 color, float thickness) {
    auto* draw = ImGui::GetOverlayDrawList();

    // Outline
    draw->AddLine(ImVec2(x, y), ImVec2(x2, y2), ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, .5f)), thickness + 2.0f);

    // Main line
    draw->AddLine(ImVec2(x, y), ImVec2(x2, y2), ImGui::GetColorU32(color), thickness);
}

void visuals::opengl::draw_esp_line(math::vec3 center, float x1, float y1, float z1, float x2, float y2, float z2, ImVec4 color) {
    math::vec3 xy1, xy2;

    math::vec3 pos_1 = math::vec3(center.x + x1, center.y + y1, center.z + z1);
    math::vec3 pos_2 = math::vec3(center.x + x2, center.y + y2, center.z + z2);

    if (functions::client::world_to_screen(pos_1, xy1) && functions::client::world_to_screen(pos_2, xy2))
        visuals::opengl::draw_line(xy1.x, xy1.y, xy2.x, xy2.y, color, 2);
}

void visuals::opengl::draw_3d_box(math::vec3 Center, float w, float h, ImVec4 Color) {
    opengl::draw_esp_line(Center, -w, -w, 0, w, -w, 0, Color);
    opengl::draw_esp_line(Center, -w, -w, 0, -w, w, 0, Color);
    opengl::draw_esp_line(Center, w, w, 0, w, -w, 0, Color);
    opengl::draw_esp_line(Center, w, w, 0, -w, w, 0, Color);

    opengl::draw_esp_line(Center, -w, -w, 0, -w, -w, h, Color);
    opengl::draw_esp_line(Center, -w, w, 0, -w, w, h, Color);
    opengl::draw_esp_line(Center, w, -w, 0, w, -w, h, Color);
    opengl::draw_esp_line(Center, w, w, 0, w, w, h, Color);

    opengl::draw_esp_line(Center, -w, -w, h, w, -w, h, Color);
    opengl::draw_esp_line(Center, -w, -w, h, -w, w, h, Color);
    opengl::draw_esp_line(Center, w, w, h, w, -w, h, Color);
    opengl::draw_esp_line(Center, w, w, h, -w, w, h, Color);
}

void visuals::opengl::corner_bounding(float x, float y, float w, float h, ImVec4 color, float thickness) {
    opengl::draw_line(x + (w / 2), y + h, x + (w / 2) - (w / 3), y + h, color, thickness);
    opengl::draw_line(x - (w / 2), y + h, x - (w / 2) + (w / 3), y + h, color, thickness);

    opengl::draw_line(x - (w / 2), y, x - (w / 2) + (w / 3), y, color, thickness);
    opengl::draw_line(x + (w / 2), y, x + (w / 2) - (w / 3), y, color, thickness);

    opengl::draw_line(x - (w / 2), y, x - (w / 2), y + (w / 3), color, thickness);
    opengl::draw_line(x + (w / 2), y, x + (w / 2), y + (w / 3), color, thickness);

    opengl::draw_line(x - (w / 2), y + h, x - (w / 2), y + h - (w / 3), color, thickness);
    opengl::draw_line(x + (w / 2), y + h, x + (w / 2), y + h - (w / 3), color, thickness);
}

void visuals::opengl::two_d_bounding(float x, float y, float w, float h, ImVec4 color, float thickness) {
    opengl::draw_line(x + (w / 2), y + h, x + (w / 2) - (w / 1), y + h, color, thickness);
    opengl::draw_line(x - (w / 2), y + h, x - (w / 2) + (w / 1), y + h, color, thickness);

    opengl::draw_line(x - (w / 2), y, x - (w / 2) + (w / 1), y, color, thickness);
    opengl::draw_line(x + (w / 2), y, x + (w / 2) - (w / 1), y, color, thickness);

    opengl::draw_line(x - (w / 2), y, x - (w / 2), y + (w / 1), color, thickness);
    opengl::draw_line(x + (w / 2), y, x + (w / 2), y + (w / 1), color, thickness);

    opengl::draw_line(x - (w / 2), y + h, x - (w / 2), y + h - (w / 1), color, thickness);
    opengl::draw_line(x + (w / 2), y + h, x + (w / 2), y + h - (w / 1), color, thickness);
}

void visuals::opengl::two_d_bounding_with_shader(float x, float y, float w, float h, ImVec4 color, float thickness) {
    // Aligned with the bounding box
    opengl::draw_rect(x - (w / 2), y, w, h, ImVec4(0.f, 0.f, 0.f, 0.5f));

    opengl::draw_line(x + (w / 2), y + h, x + (w / 2) - (w / 1), y + h, color, thickness);
    opengl::draw_line(x - (w / 2), y + h, x - (w / 2) + (w / 1), y + h, color, thickness);

    opengl::draw_line(x - (w / 2), y, x - (w / 2) + (w / 1), y, color, thickness);
    opengl::draw_line(x + (w / 2), y, x + (w / 2) - (w / 1), y, color, thickness);

    opengl::draw_line(x - (w / 2), y, x - (w / 2), y + (w / 1), color, thickness);
    opengl::draw_line(x + (w / 2), y, x + (w / 2), y + (w / 1), color, thickness);

    opengl::draw_line(x - (w / 2), y + h, x - (w / 2), y + h - (w / 1), color, thickness);
    opengl::draw_line(x + (w / 2), y + h, x + (w / 2), y + h - (w / 1), color, thickness);
}

void visuals::opengl::draw_crosshair(float size, ImVec4 color) {
    uint32_t width, height = 0;

    width = structs::screen->width / 2;
    height = structs::screen->height / 2;
    const auto cross_hair_type = static_cast<globals::menu_options::visuals::cross_hair_type>(globals::menu_options::visuals::cross_hair_selected);

    switch (cross_hair_type) {
    case globals::menu_options::visuals::cross_hair_type::cross_plus:
        opengl::draw_line(width, height - 45, width, height - 2, color, size);
        opengl::draw_line(width - 45, height, width - 2, height, color, size);
        opengl::draw_line(width + 45, height, width + 2, height, color, size);
        opengl::draw_line(width, height + 45, width, height + 2, color, size);
        break;
    case globals::menu_options::visuals::cross_hair_type::cross_x:
        opengl::draw_line(width + 25, height + 25, width - 25, height - 25, color, size);
        opengl::draw_line(width - 25, height + 25, width + 25, height - 25, color, size);
        break;
    }
}

void visuals::opengl::draw_health_bar(const math::vec3 &head, const math::vec3 &feet, float health, float max_health) {
    const float height = ::abs(feet.y - head.y);

    if (height <= 0.f || max_health <= 0.f)
        return;

    constexpr float bar_width = 4.f;
    constexpr float spacing = 4.f;

    const float box_left = head.x - (height * .25f);
    const float bar_right = box_left - spacing;
    const float bar_left = bar_right - bar_width;

    const float health_percent = std::clamp(health / max_health, 0.f, 1.f);

    auto *draw = ImGui::GetBackgroundDrawList();

    // backgorund
    draw->AddRectFilled(ImVec2(bar_left, head.y), ImVec2(bar_right, feet.y), IM_COL32(20, 20, 20, 225));

    const float health_height = height * health_percent;

    draw->AddRectFilled(ImVec2(bar_left, feet.y - health_height), ImVec2(bar_right, feet.y), IM_COL32(0, 255, 0, 255));
}

void visuals::opengl::draw_visuals() {

    const auto center_x = structs::screen->width / 2;
    const auto center_y = structs::screen->height / 2;

    if (structs::local_player == nullptr || structs::ent == nullptr)
        return;

    const auto max_players = static_cast<uint32_t>(std::size(structs::ent->entites));
    const auto player_count = (std::min)(globals::game_vars::player_count, max_players);
    const auto box_type = static_cast<globals::menu_options::visuals::box_type>(globals::menu_options::visuals::box_selected);
    const auto snaplines = globals::menu_options::visuals::snaplines;
    const auto names = globals::menu_options::visuals::name;
    const auto dist = globals::menu_options::visuals::dist; 
    const auto health_bar = globals::menu_options::visuals::health_bar;

    for (uint32_t i = 0; i < player_count; i++) {
        auto& enemy = structs::ent->entites[i];

        if (enemy == nullptr)
            continue;

        if (functions::client::is_me(enemy) || functions::client::is_alive(enemy))
            continue;

        const auto color = functions::client::is_friend(enemy) ? globals::colors::imgui::green : globals::colors::imgui::red;

        math::vec3 head_screen, feet_screen;
        if (!functions::client::world_to_screen(enemy->origin1, head_screen))
            continue;

        if (!functions::client::world_to_screen(enemy->origin2, feet_screen))
            continue;

        const auto width = fabs((head_screen.y - feet_screen.y) / 2.f);
        const auto height = width * 2.f;

        if (snaplines)
            opengl::draw_line(center_x, globals::menu_options::visuals::snap_pos, feet_screen.x, feet_screen.y, color, 1);

        switch (box_type) {
        case globals::menu_options::visuals::box_type::two_2d:
            opengl::two_d_bounding(head_screen.x, head_screen.y, width, height, color, 1);
            break;
        case globals::menu_options::visuals::box_type::two_2d_shder:
            opengl::two_d_bounding_with_shader(head_screen.x, head_screen.y, width, height, color, 1);
            break;
        case globals::menu_options::visuals::box_type::corner:
            opengl::corner_bounding(head_screen.x, head_screen.y, width, height, color, 1);
            break;
        case globals::menu_options::visuals::box_type::three_d:
            opengl::draw_3d_box(enemy->origin2, 1, 5, color);
            break;
        }

        if (names)
            opengl::draw_text_shader(functions::va(" [ %s ] ", enemy->name), head_screen.x, head_screen.y - 60, globals::colors::imgui::white, globals::colors::imgui::blue, globals::align::x_center);

        if (dist)
            opengl::draw_text_shader(functions::va(" [ %.2fm ] ", structs::local_player->origin1.distance(enemy->origin1) / 100.f), head_screen.x, head_screen.y - 41.5f, globals::colors::imgui::white, globals::colors::imgui::blue, globals::align::x_center);

        if (health_bar)
            opengl::draw_health_bar(head_screen, feet_screen, enemy->current_health, 100);
            
    }
    opengl::draw_crosshair(1, globals::colors::imgui::blue);
}