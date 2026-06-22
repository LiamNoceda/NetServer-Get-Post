cmake_minimum_required(VERSION 3.15)
project(GrapeSpaceServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew" "/usr/local")
endif()

find_package(Crow REQUIRED)

add_executable(server 
    main.cc
)

target_link_libraries(server PRIVATE Crow::Crow)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/templates"
    "$<TARGET_FILE_DIR:server>/templates"
)
