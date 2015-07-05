prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${EXEC_INSTALL_PREFIX}
libdir=${LIB_INSTALL_DIR}
includedir=${INCLUDE_INSTALL_DIR}

Name: ${PROJECT_NAME}cc
Description: The Cover Art Archive Client Library.
URL: http://musicbrainz.org/doc/libcoverart
Version: ${PROJECT_VERSION}
Requires.private: neon >= 0.25, jansson
Libs: -L${LIB_INSTALL_DIR} -lcoverartcc
Cflags: -I${INCLUDE_INSTALL_DIR}

