# depends
FIND_PACKAGE(YamlCpp REQUIRED)

INCLUDE(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(closefrom HAVE_CLOSEFROM)

# flags
IF(HAVE_CLOSEFROM)
	ADD_DEFINITIONS(-DHAVE_CLOSEFROM)
ENDIF(HAVE_CLOSEFROM)

# sources
SET(LIBDONATALLO_SOURCES
	database.cc
	detector.cc
	detectorchain.cc
	detectorfactory.cc
	detectors/alwaysdetector.cc
	detectors/opsysdetector.cc
	result.cc
)

SET(LIBDONATALLO_HEADERS
	database.hh
	detector.hh
	detectorchain.hh
	detectorfactory.hh
	detectors/alwaysdetector.hh
	detectors/opsysdetector.hh
	project.hh
	result.hh
)

IF(UNIX)
	SET(LIBDONATALLO_SOURCES ${LIBDONATALLO_SOURCES}
		util/processreader.cc
		detectors/fileinetcdetector.cc
		detectors/packagedetector.cc
		detectors/unamesdetector.cc
	)

	SET(LIBDONATALLO_HEADERS ${LIBDONATALLO_HEADERS}
		util/processreader.hh
		detectors/fileinetcdetector.hh
		detectors/packagedetector.hh
		detectors/unamesdetector.hh
	)
ENDIF(UNIX)

# targets
INCLUDE_DIRECTORIES(SYSTEM ${YAMLCPP_INCLUDE_DIRS})
ADD_LIBRARY(donatallo SHARED ${LIBDONATALLO_SOURCES} ${LIBDONATALLO_HEADERS})
TARGET_LINK_LIBRARIES(donatallo ${YAMLCPP_LIBRARIES})

# installation
IF(SYSTEMWIDE OR STANDALONE)
	INSTALL(TARGETS donatallo LIBRARY DESTINATION ${LIBDIR})
ENDIF(SYSTEMWIDE OR STANDALONE)
