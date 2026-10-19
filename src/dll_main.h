#pragma once 
#pragma comment(lib, "opengl32.lib")

 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <array>
#include <numbers>
#include <cmath>
#include <algorithm>
#include <Windows.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

#include "minhook/MinHook.h"

#include "engine/structs.h"
#include "engine/globals.h"
#include "engine/functions.h"
#include "engine/menu_interface.h"
#include "engine/visuals.h"
#include "engine/hooks.h"