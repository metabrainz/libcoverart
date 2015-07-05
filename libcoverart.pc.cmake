prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${EXEC_INSTALL_PREFIX}
libdir=${LIB_INSTALL_DIR}
includedir=${INCLUDE_INSTALL_DIR}

Name: ${PROJECT_NAME}
Description: The Cover Art Archive Client Library C interface.
URL: http://musicbrainz.org/doc/libcoverart
Version: ${PROJECT_VERSION}
Requires.private: ${PROJECT_NAME}cc
Libs: -L${LIB_INSTALL_DIR} -lcoverart
Cflags: -I${INCLUDE_INSTALL_DIR}

