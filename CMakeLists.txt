cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
        
SDL2Test
src/Main.cpp 
src/engine/Init.h 
src/AnimatedTexture.h 
src/Particles.h 
src/engine/Sprite.h 
src/TestHeader.h
src/engine/Camera.h
src/engine/WorldSprite.h
src/ACircle2.h
src/TestMapGenerator.h
src/engine/Scene.h
src/Car1.h
src/engine/math/CompositeFloat.h
src/engine/math/NonPositionalVector.h
src/engine/math/PositionalVector.h
src/engine/math/PseudoNonPositionalVector.h
src/engine/VectorSprite.h
src/something.h
)

target_link_libraries(SDL2Test ${SDL2_LIBRARIES})
target_link_libraries(SDL2Test SDL2_image::SDL2_image)
