cmake_minimum_required(VERSION 3.7)
project(Box2DSFML)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Brick.cpp Brick.h helper.h constants.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
else()
    message(FATAL_ERROR "SFML not found")
endif()

set(BOX2D_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/)
set(BOX2D_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/Build/gmake/bin/Release/)
set(BOX2D_LIBRARY Box2D)

include_directories(${BOX2D_INCLUDE_DIR})
link_directories(${BOX2D_LIBRARY_DIR})
add_library(${BOX2D_LIBRARY} SHARED IMPORTED)
set_property(TARGET ${BOX2D_LIBRARY} PROPERTY IMPORTED_LOCATION ${BOX2D_LIBRARY_DIR}/libBox2D.so)
target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARY})
