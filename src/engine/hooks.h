#pragma once 

namespace hooks {
    void init_boi();
    void toggle_input();
    void load_hooks();
    void unload_hooks();

    namespace opengl {
        LRESULT wnd_proc_hook(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparma);
        BOOL WINAPI wgl_swap_buffers(HDC hdc);
    }
}