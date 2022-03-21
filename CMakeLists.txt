cmake_minimum_required(VERSION 3.16)
project(ParticlesAnimation VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-static-libstdc++ -static-libgcc)

add_executable(
        ParticlesAnimation
        src/Particle/Particle.cpp
        src/Particle/Particle.hpp
        src/Random/Random.cpp
        src/Random/Random.hpp
        src/app.config.hpp
        src/main.cpp
)

target_include_directories(
        ParticlesAnimation PRIVATE
        lib/SDL2/include
)
target_link_libraries(
        ParticlesAnimation
        ${PROJECT_SOURCE_DIR}/lib/SDL2/lib/x64/SDL2.lib
        ${PROJECT_SOURCE_DIR}/lib/SDL2/lib/x64/SDL2main.lib
)

