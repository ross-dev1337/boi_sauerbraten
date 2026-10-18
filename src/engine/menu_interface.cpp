#include "dll_main.h"
 
void menu_interface::draw_ui() {
    POINT mouse_pos = {0, 0};
    GetCursorPos(&mouse_pos);
    ScreenToClient(globals::window, &mouse_pos);

    ImGui::GetIO().MousePos = ImVec2(mouse_pos.x, mouse_pos.y);
    ImGui::GetIO().MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? true : false;

    ImGuiStyle &style = ImGui::GetStyle();
    ImGuiIO &io = ImGui::GetIO();
    style.WindowPadding = ImVec2(5, 5);
    style.WindowRounding = 5.f;
    style.FramePadding = ImVec2(2, 2);
    style.FrameRounding = 5.f;
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(4, 3);
    style.IndentSpacing = 25.f;
    style.ItemSpacing = ImVec2(5, 5);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.GrabRounding = 5.f;

    io.WantCaptureKeyboard = true;
    io.WantCaptureMouse = true;

    style.WindowMinSize.x = 400;
    style.WindowMinSize.y = 400;

    if (globals::menu_options::is_open) {
        ImGui::Begin("BOI - Sauerbraten", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Aimbot Options");
        ImGui::Separator();
        ImGui::Checkbox("Aimbot", &globals::menu_options::aimbot::aimbot);
        ImGui::Separator();

        ImGui::Text("Visual Options");
        ImGui::Separator();
        ImGui::Checkbox("Draw SnapLines", &globals::menu_options::visuals::snaplines);
        ImGui::SliderInt("SnapLine Posision", &globals::menu_options::visuals::snap_pos, 0, 1337);
        menu_interface::handle_combo_box_options();
        ImGui::Checkbox("Draw Names", &globals::menu_options::visuals::name);
        ImGui::Checkbox("Draw Distance", &globals::menu_options::visuals::dist);
        ImGui::Checkbox("Health Bar", &globals::menu_options::visuals::health_bar);

        ImGui::End();
    }
}

void menu_interface::handle_combo_box_options() {
    
    for (const auto& [type, name] : globals::menu_options::visuals::boxes) {
        if (globals::menu_options::visuals::box_selected == type) {
            globals::menu_options::visuals::current_box = name;
            break;
        }
    }

    if (ImGui::BeginCombo("Box Type", globals::menu_options::visuals::current_box)) {
        for (const auto& [type, name] : globals::menu_options::visuals::boxes) {
            const bool selected = globals::menu_options::visuals::box_selected == type;

            if (ImGui::Selectable(name, selected))
                globals::menu_options::visuals::box_selected = type;

            if (selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    for (const auto& [type, name] : globals::menu_options::visuals::crosshairs) {
        if (globals::menu_options::visuals::cross_hair_selected == type) {
            globals::menu_options::visuals::current_cross_hair = name;
            break;
        }
    }

    if (ImGui::BeginCombo("Cross Hair Type", globals::menu_options::visuals::current_cross_hair)) {
        for (const auto& [type, name] : globals::menu_options::visuals::crosshairs) {
            const bool selected = globals::menu_options::visuals::cross_hair_selected == type;

            if (ImGui::Selectable(name, selected))
                globals::menu_options::visuals::cross_hair_selected = type;

            if (selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

void menu_interface::toggle_open() {
    !globals::menu_options::is_open ? globals::menu_options::is_open = true : globals::menu_options::is_open = false;
    functions::sdl::set_relative_mouse_mode(!globals::menu_options::is_open);
}