PROJECT(Donatallo)

# meta
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# options
OPTION(SYSTEMWIDE "Build for systemwide installation" OFF)
OPTION(STANDALONE "Build for creating standalone package" OFF)

IF(SYSTEMWIDE)
	SET(BINDIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE STRING "Where to install binaries")
	SET(LIBDIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE STRING "Where to install libraries")
	SET(DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share" CACHE STRING "Root directory for data files")
	SET(DATADIR "${DATAROOTDIR}/donatallo" CACHE STRING "Where to install data files")
ELSEIF(STANDALONE)
	SET(BINDIR "." CACHE STRING "Where to install binaries")
	SET(LIBDIR "." CACHE STRING "Where to install libraries")
	SET(DATAROOTDIR "." CACHE STRING "Root directory for data files")
	SET(DATADIR "data" CACHE STRING "Where to install data files")
ENDIF(SYSTEMWIDE)

# depends
IF(NOT EXISTS ${PROJECT_SOURCE_DIR}/data/database/meta.yml)
	MESSAGE(FATAL_ERROR "The database submodule was not checked out to data/database\nIt is likely that you forgot to run\n  git submodule init && git submodule update")
ENDIF(NOT EXISTS ${PROJECT_SOURCE_DIR}/data/database/meta.yml)

# flags
SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

IF(SYSTEMWIDE OR STANDALONE)
	ADD_DEFINITIONS(-DDONATALLO_DATADIR="${DATADIR}")
ELSE(SYSTEMWIDE OR STANDALONE)
	ADD_DEFINITIONS(-DDONATALLO_DATADIR="${PROJECT_SOURCE_DIR}/data")
ENDIF(SYSTEMWIDE OR STANDALONE)

# libdonatallo
INCLUDE_DIRECTORIES(BEFORE .)

# subdirectories
ADD_SUBDIRECTORY(libdonatallo)
ADD_SUBDIRECTORY(donatallo-cli)

ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)

# installation
IF(SYSTEMWIDE OR STANDALONE)
	INSTALL(DIRECTORY data/database DESTINATION ${DATADIR} FILES_MATCHING PATTERN "*.yml")
	INSTALL(DIRECTORY data/scripts DESTINATION ${DATADIR})
ENDIF(SYSTEMWIDE OR STANDALONE)
