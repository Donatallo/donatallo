ADD_DEFINITIONS(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

ADD_EXECUTABLE(libdonatallo-test libdonatallo-test.cc)
ADD_TEST(libdonatallo-test libdonatallo-test)
