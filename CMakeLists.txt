cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(FriggBerry)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

find_package(OpenGL REQUIRED)



find_package(SDL2 REQUIRED)
message(STATUS "SDL2_INCLUDE_DIR = ${SDL2_INCLUDE_DIR}")
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(FriggBerry src/main.cpp)

message(STATUS "SDL2_LIBRARIES = ${SDL2_LIBRARIES}")
message(STATUS "SDL2_SHARED_LIBRARY = ${SDL2_SHARED_LIBRARY}")
message(STATUS "SDL2_LINK_FLAGS = ${SDL2_LINK_FLAGS}")

add_library(SDL2_SHARED SHARED IMPORTED)
set_property(TARGET SDL2_SHARED PROPERTY IMPORTED_LOCATION ${SDL2_SHARED_LIBRARY})
list(GET SDL2_LIBRARIES 1 SDL2_LIB)
message(STATUS "SDL2_LIB = ${SDL2_LIB}")
set_property(TARGET SDL2_SHARED PROPERTY IMPORTED_IMPLIB  ${SDL2_LIB})

set(CMAKE_PREFIX_PATH "F:/Projects/Ymir/shared/glew-2.1.0/include")
set(CMAKE_LIBRARY_PATH "F:/Projects/Ymir/shared/glew-2.1.0/lib/Release/Win32")
find_package(GLEW REQUIRED)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

target_link_libraries(FriggBerry ${SDL2_LIBRARIES})
set_target_properties(FriggBerry PROPERTIES LINK_FLAGS ${SDL2_LINK_FLAGS})
target_link_libraries(FriggBerry ${SDL2_SHARED} ${OPENGL_LIBRARY})
