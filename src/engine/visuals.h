#pragma once
 
namespace visuals {
    namespace opengl {
        void draw_rect(float x, float y, float width, float height, ImVec4 color);
        void draw_string(const char* string, float x, float y, ImVec4 color);
        void draw_text_shader(const char* string, float x, float y, ImVec4 color, ImVec4 color2, globals::align op);
        void draw_line(float x, float y, float x2, float y2, ImVec4 color, float thickness);
        void draw_esp_line(math::vec3 center, float x1, float y1, float z1, float x2, float y2, float z2, ImVec4 color);
        void draw_esp_line(math::vec3 center, float x1, float y1, float z1, float x2, float y2, float z2, ImVec4 color);
        void draw_3d_box(math::vec3 Center, float w, float h, ImVec4 Color);
        void corner_bounding(float x, float y, float w, float h, ImVec4 color, float thickness);
        void two_d_bounding(float x, float y, float w, float h, ImVec4 color, float thickness);
        void two_d_bounding_with_shader(float x, float y, float w, float h, ImVec4 color, float thickness);
        void draw_crosshair(float size, ImVec4 color);
        void draw_triangle_pointer(float center_x, float center_y, const math::vec3* offset, ImVec4 color);
        void draw_view_angles(uint32_t i, ImVec4 color);
        void draw_health_bar(const math::vec3& head, const math::vec3& feet, float health, float max_health);
        void draw_visuals();
    }
}