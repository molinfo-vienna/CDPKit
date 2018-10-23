INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp
    MapTest.cpp                     # TODO
    MultiMapTest.cpp                # TODO
    ArrayTest.cpp                   # TODO
    IndirectArrayTest.cpp           # TODO
    DereferencerTest.cpp
    IndexedElementIteratorTest.cpp
    StreamDataReaderTest.cpp
    PropertyValueTest.cpp
    PropertyValueProductTest.cpp
    BronKerboschAlgorithmTest.cpp
    DGCoordinatesOptimizerTest.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(util-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(util-test-suite cdpl-util-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Util" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/util-test-suite")
