INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp

    MMFF94TestData.cpp
    MMFF94AtomTyperTest.cpp
    MMFF94ChargeCalculatorTest.cpp
    MMFF94BondStretchingInteractionParameterizerTest.cpp
    MMFF94AngleBendingInteractionParameterizerTest.cpp
    MMFF94StretchBendInteractionParameterizerTest.cpp
    MMFF94OutOfPlaneBendingInteractionParameterizerTest.cpp
    MMFF94TorsionInteractionParameterizerTest.cpp
    MMFF94VanDerWaalsInteractionParameterizerTest.cpp
    MMFF94EnergyFunctionsTest.cpp
    MMFF94EnergyCalculatorTest.cpp

    OptimolLogReader.cpp
    TestUtils.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(forcefield-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(forcefield-test-suite cdpl-forcefield-shared cdpl-chem-shared cdpl-internal-static ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::ForceField" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/forcefield-test-suite")
