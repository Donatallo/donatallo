# sources
SET(DONATALLO_CLI_SOURCES
	main.cc
)

# targets
ADD_EXECUTABLE(donatallo-cli ${DONATALLO_CLI_SOURCES})
TARGET_LINK_LIBRARIES(donatallo-cli donatallo)
