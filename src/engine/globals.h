#pragma once
 
namespace globals {
    inline HWND window = 0;
    inline uint64_t game_base = 0;
    inline bool run = false;
    inline WNDPROC org_wnd_proc = nullptr;
    inline uint64_t mouse_move = 0;

    enum class align : uint8_t {
        x_left,
        x_center,
        x_right
    };

    namespace menu_options {
        inline bool is_open = false;
        
        namespace aimbot {
            inline bool aimbot = false;
        }

        namespace visuals {
            
            enum class box_type : std::uint8_t {
                none,
                two_2d,
                two_2d_shder,
                corner,
                three_d
            };

            inline const char* current_box = "None";

            inline constexpr std::array boxes {
                std::pair{box_type::none, "None"},
                std::pair{box_type::two_2d, "2D"},
                std::pair{box_type::two_2d_shder, "2D Shader"},
                std::pair{box_type::corner, "Corner"},
                std::pair{box_type::three_d, "3D"}
            };

            enum class cross_hair_type : std::uint8_t {
                none,
                cross_x,
                cross_plus
            };

            inline const char* current_cross_hair = "None";
            
            constexpr std::array crosshairs {
                std::pair{cross_hair_type::none, "None"},
                std::pair{cross_hair_type::cross_plus, "+"},
                std::pair{cross_hair_type::cross_x, "X"}
            };

        
            inline bool snaplines = false;
            inline int snap_pos = 0;
            inline bool name = false;
            inline bool dist = false;
            inline bool health_bar = false;

            inline box_type box_selected = box_type::none;
            inline cross_hair_type cross_hair_selected = cross_hair_type::none;
        }
    }

    namespace game_vars {
        inline uint32_t player_count = 0;
        inline uintptr_t ray_cube = 0; 
    }

    namespace colors {
        namespace imgui {
            inline ImVec4 blue{0.f, .3f, .9f, 1};
            inline ImVec4 light_blue{.1f, .5f, 1, 1};
            inline ImVec4 red{1, 0, 0, 1};
            inline ImVec4 white{1, 1, 1, 1};
            inline ImVec4 black{0, 0, 0, .5f};
            inline ImVec4 green{0, .8f, .1f, 1};
            inline ImVec4 yellow{.9f, .9f, .1f, 1};
        }
    }
}