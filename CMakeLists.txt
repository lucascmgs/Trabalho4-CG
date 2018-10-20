project(Trabalho4)
add_executable(Trabalho4 main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Trabalho4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )