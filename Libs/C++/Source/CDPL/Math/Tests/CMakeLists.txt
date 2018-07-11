INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp
    SpecialFunctionsTest.cpp
    VectorArrayTest.cpp                    # TODO
    VectorArrayFunctionsTest.cpp           # TODO
    JacobiDiagonalizationTest.cpp
    MLRModelTest.cpp
    RangeTest.cpp
    SliceTest.cpp
    CommonTypeTest.cpp
    TypeTraitsTest.cpp
    FunctionalTest.cpp
    VectorAssignmentTest.cpp
    MatrixAssignmentTest.cpp
    QuaternionAssignmentTest.cpp
    ExpressionTest.cpp
    VectorTest.cpp
    VectorExpressionTest.cpp
    VectorProxyTest.cpp
    VectorAdapterTest.cpp
    MatrixTest.cpp
    MatrixExpressionTest.cpp 
    MatrixProxyTest.cpp
    MatrixAdapterTest.cpp
    AffineTransformTest.cpp
    QuaternionTest.cpp
    QuaternionExpressionTest.cpp
    QuaternionAdapterTest.cpp
    DirectAssignmentProxyTest.cpp
    LUDecompositionTest.cpp
    SVDecompositionTest.cpp
    LinearSolveTest.cpp
    IOTest.cpp
    BFGSMinimizerTest.cpp
    KabschAlgorithmTest.cpp
    #VectorIteratorTest.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(math-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(math-test-suite cdpl-math-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Math" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/math-test-suite")
