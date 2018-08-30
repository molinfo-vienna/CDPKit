INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(confgen-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(confgen-test-suite cdpl-confgen-shared cdpl-chem-shared cdpl-forcefield-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::ConfGen" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/confgen-test-suite")
