cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(FriggBerry)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(FriggBerry src/main.cpp)

#add_library()

message(STATUS "SDL2_LIBRARIES = ${SDL2_LIBRARIES}")
message(STATUS "SDL2_SHARED_LIBRARY = ${SDL2_SHARED_LIBRARY}")
message(STATUS "SDL2_LINK_FLAGS = ${SDL2_LINK_FLAGS}")

add_library(SDL2_SHARED SHARED IMPORTED)
set_property(TARGET SDL2_SHARED PROPERTY IMPORTED_LOCATION ${SDL2_SHARED_LIBRARY})
list(GET SDL2_LIBRARIES 1 SDL2_LIB)
message(STATUS "SDL2_LIB = ${SDL2_LIB}")
set_property(TARGET SDL2_SHARED PROPERTY IMPORTED_IMPLIB  ${SDL2_LIB})

target_link_libraries(FriggBerry ${SDL2_LIBRARIES})
set_target_properties(FriggBerry PROPERTIES LINK_FLAGS ${SDL2_LINK_FLAGS})
target_link_libraries(FriggBerry ${SDL2_SHARED})
