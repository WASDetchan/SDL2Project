cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

set(SDL2_DIR "F:/Program Files/SDL2-devel-2.28.1-VC/SDL2-2.28.1/cmake")
set(SDL2_image_DIR "F:/Program Files/SDL2-devel-2.28.1-VC/SDL2_image-2.6.3/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test Main.cpp Main.cpp Init.h AnimatedTexture.h Particles.h Sprite.h TestHeader.h
        Camera.h
        WorldSprite.h
        ACircle2.h
        TestMapGenerator.h
        Scene.h
)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})
target_link_libraries(SDL2Test SDL2_image::SDL2_image)
