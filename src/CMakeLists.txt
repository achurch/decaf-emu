include_directories(".")

add_subdirectory(common)
add_subdirectory(libcpu)
add_subdirectory(libgpu)
add_subdirectory(libdecaf)
add_subdirectory(libgfd)
add_subdirectory(libconfig)

add_subdirectory(decaf-cli)

if(DECAF_SDL)
    add_subdirectory(common-sdl)
    add_subdirectory(decaf-sdl)
endif()
