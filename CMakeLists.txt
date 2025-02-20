cmake_minimum_required(VERSION 3.20...3.30)

project(learnopengl
        VERSION 0.1
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glfw")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/fmt")

add_executable(learnopengl
  src/main.cpp

  deps/glad/src/glad.c
)

target_link_libraries(learnopengl PRIVATE fmt::fmt glfw)

target_include_directories(learnopengl
  PUBLIC
  "src"
  "deps/glad/include"
  "deps/glfw/include"
  "deps/fmt/include"
)
