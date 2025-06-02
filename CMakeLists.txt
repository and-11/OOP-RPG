cmake_minimum_required(VERSION 3.26)
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")
project(${MAIN_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
add_executable(${MAIN_EXECUTABLE_NAME}
    main.cpp
    enemy.cpp
    entity.cpp
    exception.cpp
    functions.cpp
    game.cpp
    visitor.cpp
    goblin.cpp 
    item.cpp
    orc.cpp 
    player.cpp 
    player_builder.cpp
    potion.cpp 
    skeleton.cpp 
    user_interface.cpp 
    wolf.cpp 
    crow.cpp
    generated/src/Helper.cpp
)
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)
target_link_libraries(oop sfml-graphics sfml-window sfml-system)
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()
copy_files(FILES date_intrare.in COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})