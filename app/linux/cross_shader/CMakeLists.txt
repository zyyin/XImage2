cmake_minimum_required(VERSION 2.8)
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
