SET(LIBDONATALLO_SOURCES
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

ADD_LIBRARY(donatallo ${LIBDONATALLO_SOURCES} ${LIBDONATALLO_HEADERS})
