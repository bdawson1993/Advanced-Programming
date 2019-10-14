option( FREEGLUT_BUILD_DEMOS "Build FreeGLUT demos." ON )

add_subdirectory(freeglut-3.2.1)

include_directories(
	freeglut-3.2.1/src
	freeglut-3.2.1/include/GL
)