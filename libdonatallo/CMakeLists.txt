FIND_PACKAGE(YamlCpp REQUIRED)

SET(LIBDONATALLO_SOURCES
	database.cc
	detector.cc
	detectorchain.cc
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
	)

	SET(LIBDONATALLO_HEADERS ${LIBDONATALLO_HEADERS}
		util/processreader.hh
	)
ENDIF(UNIX)

INCLUDE_DIRECTORIES(SYSTEM ${YAMLCPP_INCLUDE_DIRS})
ADD_LIBRARY(donatallo ${LIBDONATALLO_SOURCES} ${LIBDONATALLO_HEADERS})
TARGET_LINK_LIBRARIES(donatallo ${YAMLCPP_LIBRARIES})
