cmake_minimum_required(VERSION 3.6)
project(t1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp vert/vert.cpp mesh/mesh.cpp)
add_executable(t1 ${SOURCE_FILES})

IF (APPLE)
    include_directories (/System/Library/Frameworks)

    if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
        # Already in cache, be silent
        set(GMP_FIND_QUIETLY TRUE)
    endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)

    find_path(GMP_INCLUDE_DIR NAMES gmp.h )
    find_library(GMP_LIBRARIES NAMES gmp libgmp )
    find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx )
    MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES} " " ${GMPXX_LIBRARIES} )

    include(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)
    find_library (GLUT_LIBRARY GLUT)
    find_library (OpenGL_LIBRARY OpenGL)
    find_library (CGAL_LIBRARY CGAL)
    find_library (GMP_LIBRARY gmp)
    mark_as_advanced (GLUT_LIBRARY OpenGL_LIBRARY CGAL_LIBRARY GMP_INCLUDE_DIR GMP_LIBRARIES)
    set (EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY} ${CGAL_LIBRARY} ${GMP_LIBRARIES})
ENDIF (APPLE)

target_link_libraries(t1 ${EXTRA_LIBS})