INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include)
LINK_LIBRARIES(coverart ${NEON_LIBRARIES})
ADD_EXECUTABLE(test test.cc)
ADD_EXECUTABLE(ctest ctest.c)

IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

IF(CMAKE_COMPILER_IS_GNUCC)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
#		set_source_files_properties(ctest.c PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
		set_source_files_properties(test.cc PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

