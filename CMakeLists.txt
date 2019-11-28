# CMake entry point
cmake_minimum_required (VERSION 3.0)
# this line suppresses the ZERO_CHECK project that is usually generated
set(CMAKE_SUPPRESS_REGENERATION true)	
project (AdvancedProgramming)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)



include_directories(
	external/freeglut-3.2.1/include
)

set(SRC src)
add_executable( ${SRC}
	${SRC}/main.cpp
	${SRC}/freeglutd.dll
	${SRC}/vecmath.h
	${SRC}/Ball.h
	${SRC}/Ball.cpp
	${SRC}/Camera.cpp
	${SRC}/Camera.h
	${SRC}/Cue.cpp
	${SRC}/Cue.h
	${SRC}/GolfCourse.h
	${SRC}/GolfCourse.cpp
	${SRC}/Hole.h
	${SRC}/Hole.cpp
	${SRC}/IGameObject.h
	${SRC}/IGameObject.cpp
	${SRC}/Side.cpp
	${SRC}/Side.h
	${SRC}/TextRenderer.h
	${SRC}/TextRenderer.cpp
	${SRC}/GameController.h
	${SRC}/GameController.cpp
	${SRC}/Network.cpp
	${SRC}/Network.h

	
)

set(SRC server)
add_executable(server
	${SRC}/main.cpp
)

set(SRC src)
TARGET_LINK_LIBRARIES(${SRC} freeglut freeglut_static)


