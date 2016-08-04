INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp
    BasicFeatureTest.cpp
    FeatureTest.cpp
    BasicPharmacophoreTest.cpp
    PharmacophoreTest.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(pharm-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(pharm-test-suite cdpl-pharm-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Pharm" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/pharm-test-suite")
