INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    SHA1Test.cpp
    AddressOfTest.cpp
    PermutationTest.cpp
    RangeGeneratorTest.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(internal-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(internal-test-suite cdpl-internal-static ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Internal" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/internal-test-suite")
