cmake_minimum_required(VERSION 3.15)

project(RType LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_CLIENT "Build the client executable" ON)
option(BUILD_SERVER "Build the server executable" ON)

add_subdirectory(external/SDL3)
add_subdirectory(external/SDL3_ttf)
add_subdirectory(external/SDL3_image)

if(BUILD_CLIENT)
    file(GLOB SOURCES_CLIENT "src/graphical/*.cpp")
    add_executable(r-type_client ${SOURCES_CLIENT})
    target_include_directories(r-type_client PRIVATE include/graphical)

    target_link_libraries(r-type_client PRIVATE SDL3::SDL3)
    target_link_libraries(r-type_client PRIVATE SDL3_ttf::SDL3_ttf)
    target_link_libraries(r-type_client PRIVATE SDL3_image::SDL3_image)

    target_compile_definitions(r-type_client PRIVATE $<$<CONFIG:Debug>:DEBUG>)
endif()

if(BUILD_SERVER)
    file(GLOB SOURCES_SERVER "src/server/*.cpp")
    file(GLOB SOURCES_SERVER_TCP "src/server/tcp/*.cpp")
    file(GLOB SOURCES_SERVER_UDP "src/server/udp/*.cpp")
    file(GLOB SOURCES_SERVER_GAME "src/server/game/*.cpp")
    file(GLOB SOURCES_ECS "src/ecs/*.cpp")
    add_executable(r-type_server ${SOURCES_SERVER} ${SOURCES_SERVER_TCP} ${SOURCES_SERVER_UDP} ${SOURCES_SERVER_GAME} ${SOURCES_ECS})
    target_include_directories(r-type_server PRIVATE include/server)

    target_link_libraries(r-type_server PRIVATE SDL3::SDL3)
    target_link_libraries(r-type_server PRIVATE SDL3_ttf::SDL3_ttf)
    target_link_libraries(r-type_server PRIVATE SDL3_image::SDL3_image)

    target_compile_definitions(r-type_server PRIVATE $<$<CONFIG:Debug>:DEBUG>)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
else()
    message(STATUS "Building in Release mode")
endif()

add_compile_options(-Wall -Wextra -pedantic)