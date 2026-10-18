cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

set(PROJECT_NAME boi_sauerbraten)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_VERBOSE_MAKEFILE OFF)

project(${PROJECT_NAME})
enable_language(ASM_MASM)

get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

set(CMAKE_BUILD_TYPE Release)
set(OUTPUT_DIR ${PROJECT_DIR}/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_CURRENT_BINARY_DIR ${OUTPUT_DIR})
set(CMAKE_BINARY_DIR ${OUTPUT_DIR})
set(PROJECT_BINARY_DIR ${OUTPUT_DIR})
set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${VENDOR_DIR}/)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ASM_FILES ${PROJECT_SOURCE_DIR}/src/*.asm)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${ASM_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/dll_main.h)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS -DNDEBUG -D_WINDOWS -D_DLL)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFEST /LTCG:incremental /NXCOMPAT /DYNAMICBASE /OPT:REF /INCREMENTAL:NO /MAP /OPT:ICF /NOLOGO /TLBID:1")
target_compile_options(${PROJECT_NAME} PRIVATE /MP32 /GS- /GL /Zc:wchar_t /Gm- /O2 /Zc:inline /fp:precise /GF  /Zc:forScope /GR- /Gd /Oi /MD /std:c++latest /EHsc /nologo /diagnostics:column)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/dll_main.h)
target_link_libraries(${PROJECT_NAME} crypt32.lib winmm.lib Ws2_32.lib Normaliz.lib wldap32.lib ntdll.lib wbemuuid.lib cryptui.lib advapi32.lib strmiids.lib)