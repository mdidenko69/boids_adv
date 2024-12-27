cmake_minimum_required(VERSION 3.25)
project(boids)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(LIB_HEADERS
        src/random.h
        src/Vector2D.h
        src/Vector2D.inl
        src/Boid.h
        src/Flock.h
        src/Simulation.h
        src/KDTree.h)

set(LIB_SOURCES
        src/random.cpp
        src/Boid.cpp
        src/Flock.cpp
        src/Simulation.cpp
        src/KDTree.cpp)

#find_package(OpenMP 4.5 REQUIRED)
# 3rd party dependencies
add_subdirectory(lib)

add_library(boids ${LIB_SOURCES} ${LIB_HEADERS})
target_link_libraries(boids SFML::Graphics SFML::System)
#target_link_libraries(boids OpenMP::OpenMP_CXX SFML::Graphics SFML::System)

add_executable(simulate src/main.cpp src/cxxopts.hpp)
target_link_libraries(simulate boids)

install(TARGETS simulate DESTINATION ${INSTALL_BIN_DIR})

