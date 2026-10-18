#include "dll_main.h"

void hooks::init_boi() {
    AllocConsole();
    SetConsoleTitle("Sauerbraten - BOI");
    FILE *f = nullptr;
    freopen_s(&f, "CONOUT$", "w", stdout);

    puts("DLL - Loaded!");

    hooks::load_hooks();
}

BOOL APIENTRY DllMain(HANDLE h, uint32_t r, LPVOID lp) {
    switch (r) {
    case DLL_PROCESS_ATTACH:
        hooks::init_boi();
        break;
    case DLL_PROCESS_DETACH:
        if(lp == nullptr)
            hooks::unload_hooks();
        break;
    }
    return true;
}