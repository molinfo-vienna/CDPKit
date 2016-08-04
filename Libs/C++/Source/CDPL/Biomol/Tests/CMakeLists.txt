INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(biomol-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(biomol-test-suite cdpl-biomol-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Biomol" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/biomol-test-suite")
