# Copyright (c) 2011-2014 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

# Change this number when adding tests to force a CMake run: 2

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

set(TEST_LIBRARIES codash)
include(CommonCTest)

install(FILES ${TEST_FILES} DESTINATION share/codash/tests COMPONENT examples)
