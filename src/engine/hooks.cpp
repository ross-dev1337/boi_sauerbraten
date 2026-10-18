#include "dll_main.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparma, LPARAM lparam);

namespace stub {
    decltype(&hooks::opengl::wgl_swap_buffers) wgl_swap_buffers;
}

void hooks::toggle_input() {
    if (GetAsyncKeyState('O') & 0x1)
        menu_interface::toggle_open();
    menu_interface::draw_ui();
}

LRESULT hooks::opengl::wnd_proc_hook(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparma) {
    if (globals::menu_options::is_open) {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparma))
            return 0;

        switch (umsg) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            return 0;
        }
    }
    return CallWindowProc(globals::org_wnd_proc, hwnd, umsg, wparam, lparma);
}

BOOL WINAPI hooks::opengl::wgl_swap_buffers(HDC hdc) {
    // Our own GL context so ImGui never touches the game's state (shaders, VBOs, FBOs, texture units...)
    static HGLRC our_ctx = nullptr;

    const HGLRC game_ctx = wglGetCurrentContext();
    if (!our_ctx) {
        our_ctx = wglCreateContext(hdc);
        if (!our_ctx)
            return stub::wgl_swap_buffers(hdc);
    }
    wglMakeCurrent(hdc, our_ctx);

    if (!globals::run) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("C:\\Development\\cheats\\PC\\Learn Game Hacking\\cube_new\\boi_ac\\fonts\\DroidSans.ttf", 18.f);

        ImGui_ImplWin32_Init(globals::window);
        ImGui_ImplOpenGL2_Init();

        globals::run = true;
    }

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    functions::rebase();
    hooks::toggle_input();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    wglMakeCurrent(hdc, game_ctx);
    return stub::wgl_swap_buffers(hdc);
}

void hooks::load_hooks() {
    if (const auto status = MH_Initialize(); status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED) {
        fprintf(stderr, "MH_Initialize failed: %s\n", MH_StatusToString(status));
        return;
    }

    globals::window = FindWindowA(nullptr, "Cube 2: Sauerbraten");
    if (globals::window == nullptr) {
        fprintf(stderr, "Failed to find game window\n");
        return;
    }

    functions::rebase();

    const auto create_hook = [](uintptr_t target, void *detour, void **original) -> bool {
        const auto hook_status = MH_CreateHook(reinterpret_cast<LPVOID>(target), detour, original);
        if (hook_status != MH_OK) {
            fprintf(stderr, "MH_CreateHook failed: %s\n", MH_StatusToString(hook_status));
            return false;
        }
        return true;
    };

    globals::org_wnd_proc = (WNDPROC)SetWindowLongPtr(globals::window, GWLP_WNDPROC, (LONG_PTR)hooks::opengl::wnd_proc_hook);
    globals::mouse_move = reinterpret_cast<uint64_t>(GetProcAddress(GetModuleHandleA("SDL2.dll"), "SDL_SetRelativeMouseMode"));

    const auto wgl_swap_buffers = reinterpret_cast<void *>(GetProcAddress(GetModuleHandleA("OPENGL32.dll"), "wglSwapBuffers"));
    if (!create_hook(reinterpret_cast<uintptr_t>(wgl_swap_buffers), reinterpret_cast<void*>(&hooks::opengl::wgl_swap_buffers), reinterpret_cast<void**>(&stub::wgl_swap_buffers)))
        return;

    if (const auto status = MH_EnableHook(MH_ALL_HOOKS); status != MH_OK) {
        fprintf(stderr, "MH_EnableHook failed: %s\n", MH_StatusToString(status));
        return;
    }
    puts("Hooks - loaded!");
}

void hooks::unload_hooks() {
    if (globals::org_wnd_proc) {
        SetWindowLongPtr(globals::window, GWLP_WNDPROC, (LONG_PTR)globals::org_wnd_proc);
        globals::org_wnd_proc = nullptr;
    }

    if (const auto status = MH_DisableHook(MH_ALL_HOOKS); status != MH_OK && status != MH_ERROR_NOT_INITIALIZED) {
        fprintf(stderr, "MH_DisableHook failed: %s\n", MH_StatusToString(status));
    }

    if (const auto status = MH_RemoveHook(MH_ALL_HOOKS); status != MH_OK && status != MH_ERROR_NOT_INITIALIZED) {
        fprintf(stderr, "MH_RemoveHook failed: %s\n", MH_StatusToString(status));
    }

    if (const auto status = MH_Uninitialize(); status != MH_OK && status != MH_ERROR_NOT_INITIALIZED) {
        fprintf(stderr, "MH_Uninitialize failed: %s\n", MH_StatusToString(status));
    } else {
        puts("DLL - Unloaded!");
    }

    if (globals::run) {
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
}
