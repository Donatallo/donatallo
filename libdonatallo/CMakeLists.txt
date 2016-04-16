FIND_PACKAGE(YamlCpp REQUIRED)

SET(LIBDONATALLO_SOURCES
	database.cc
	detector.cc
	detectorchain.cc
	result.cc
)

SET(LIBDONATALLO_HEADERS
	database.hh
	detector.hh
	detectorchain.hh
	detectorfactory.hh
	project.hh
	result.hh
)

INCLUDE_DIRECTORIES(SYSTEM ${YAMLCPP_INCLUDE_DIRS})
ADD_LIBRARY(donatallo ${LIBDONATALLO_SOURCES} ${LIBDONATALLO_HEADERS})
TARGET_LINK_LIBRARIES(donatallo ${YAMLCPP_LIBRARIES})
