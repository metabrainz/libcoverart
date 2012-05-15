INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PKG_NEON neon)

FIND_PATH(NEON_INCLUDE_DIR ne_request.h
    PATHS
    ${PKG_NEON_INCLUDE_DIRS}
    /usr/include
    /usr/local/include
    PATH_SUFFIXES neon
)

FIND_LIBRARY(NEON_LIBRARIES neon
    ${PKG_NEON_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Neon DEFAULT_MSG NEON_LIBRARIES NEON_INCLUDE_DIR)
