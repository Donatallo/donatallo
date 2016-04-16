ADD_DEFINITIONS(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

ADD_EXECUTABLE(libdonatallo-test libdonatallo-test.cc)
TARGET_LINK_LIBRARIES(libdonatallo-test donatallo)
ADD_TEST(libdonatallo-test libdonatallo-test)

IF(UNIX)
	ADD_EXECUTABLE(processreader-test processreader-test.cc)
	TARGET_LINK_LIBRARIES(processreader-test donatallo)
	ADD_TEST(processreader-test processreader-test)
ENDIF(UNIX)
