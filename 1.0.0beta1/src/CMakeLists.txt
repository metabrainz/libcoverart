SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../include ${NEON_INCLUDE_DIR} ${JANSSON_INCLUDE_DIR})

SET(_sources HTTPFetch.cc CoverArt.cc ReleaseInfo.cc ImageList.cc Image.cc
	Thumbnails.cc TypeList.cc caa_c.cc Type.cc)

ADD_EXECUTABLE(make-c-interface make-c-interface.cc xmlParser.cpp)

ADD_CUSTOM_COMMAND(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/caa_c.cc ${CMAKE_CURRENT_BINARY_DIR}/caa_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/coverart/caa_c.h
	COMMAND make-c-interface ${CMAKE_CURRENT_SOURCE_DIR} cinterface.xml ${CMAKE_CURRENT_BINARY_DIR} caa_c.cc caa_c.h
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/caa_c.h ${CMAKE_CURRENT_BINARY_DIR}/../include/coverart
	DEPENDS make-c-interface cinterface.xml *.inc
)

ADD_CUSTOM_TARGET(src_gen DEPENDS caa_c.h)

ADD_LIBRARY(coverart SHARED ${_sources})

SET_TARGET_PROPERTIES(coverart PROPERTIES
    VERSION ${coverart_VERSION}
    SOVERSION ${coverart_SOVERSION}
    DEFINE_SYMBOL MB_API_EXPORTS
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	SET_TARGET_PROPERTIES(coverart PROPERTIES
		DEFINE_SYMBOL _COVERART_DEBUG_
	)
	IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -O0")
	ENDIF(CMAKE_COMPILER_IS_GNUCXX)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

TARGET_LINK_LIBRARIES(coverart ${NEON_LIBRARIES} ${JANSSON_LIBRARIES})

IF(WIN32)
    TARGET_LINK_LIBRARIES(coverart wsock32 winmm ws2_32)
ENDIF(WIN32)

IF(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic-errors")
		set_source_files_properties(mb4_c.cc PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
		set_source_files_properties(ReleaseInfo.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
		set_source_files_properties(ImageList.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
		set_source_files_properties(Image.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
		set_source_files_properties(Thumbnails.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
		set_source_files_properties(TypeList.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
		set_source_files_properties(CoverArt.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
		set_source_files_properties(caa_c.cc PROPERTIES COMPILE_FLAGS "-Wno-long-long")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

INSTALL(TARGETS coverart DESTINATION ${LIB_INSTALL_DIR})
