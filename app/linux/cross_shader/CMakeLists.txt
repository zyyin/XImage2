SET(CMAKE_CXX_FLAGS "-std=c++0x")
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fpermissive")
file(GLOB ALL_SRC
	"*.h"
	"*.cpp"
	)
project( main )
find_package( OpenCV REQUIRED )
add_executable( main ${ALL_SRC})
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ../../../include/ )
target_link_libraries( main ${OpenCV_LIBS} )
