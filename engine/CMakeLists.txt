cmake_minimum_required(VERSION 3.20)
project(my3DEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED) 
# Add dependencies
set(GLFW_BUILD_WAYLAND OFF)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

include_directories(include deps/glfw/include deps/glm deps/glad/include)

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp src/*/*.cpp deps/glad/src/glad.c)

add_executable(my3DEngine ${ENGINE_SOURCES})
target_link_libraries(my3DEngine glfw OpenGL::GL)
