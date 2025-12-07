cmake_minimum_required(VERSION 4.0)

project(LeetCode)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIBS lib/hashmap.c lib/hashset.c)

add_library(ds STATIC
    lib/hashmap.c
    lib/hashset.c
)

target_include_directories(ds PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(has_duplicates src/has_duplicates.c)
target_link_libraries(has_duplicates PRIVATE ds)

add_executable(binary_search src/binary_search.c)
target_link_libraries(binary_search PRIVATE ds)

# target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glm)

# add_custom_target(copy_resources ALL
# COMMAND ${CMAKE_COMMAND} -E copy_directory
# ${CMAKE_SOURCE_DIR}/res
# ${CMAKE_BINARY_DIR}/res
# )
# add_dependencies(${PROJECT_NAME} copy_resources)
