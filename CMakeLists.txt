# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Dwave)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CSS_FLAGS} "-fPIC")
set(CMAKE_BUILD_TYPE Release)

#Bring the headers into the project
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif ()

# check for libpng
pkg_check_modules (LIBPNG libpng16 REQUIRED)
if (NOT LIBPNG_FOUND)
	message(FATAL_ERROR "You don't seem to have libpng16 development libraries installed")
else ()
  include_directories (${LIBPNG_INCLUDE_DIRS})
  link_directories (${LIBPNG_LIBRARY_DIRS})
  link_libraries (${LIBPNG_LIBRARIES})
endif ()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})
  link_libraries(${GLEW_LIBRARIES})
endif()

set(glui_DIR /usr/lib/lib/cmake/glui/)
find_package(glui CONFIG REQUIRED)

add_executable(main ${SOURCES})
add_library(Dwave SHARED ${SOURCES})

target_link_libraries(main PUBLIC glui::glui) # ${ALL_LIBS})
target_link_libraries(Dwave PUBLIC glui::glui)
