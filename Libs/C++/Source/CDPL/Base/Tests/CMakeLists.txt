INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    VariantTest.cpp
    LookupKeyTest.cpp
    ControlParameterContainerTest.cpp
    LookupKeyDefinitionTest.cpp
    PropertyContainerTest.cpp
    DataIOBaseTest.cpp
    DataIOManagerTest.cpp
    DataFormatTest.cpp
    ExceptionsTest.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(base-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(base-test-suite cdpl-base-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Base" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/base-test-suite")
