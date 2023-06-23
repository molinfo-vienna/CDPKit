##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##

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

IF(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wno-self-assign-overloaded")
ENDIF()

SET(CMAKE_BUILD_TYPE "Debug")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(math-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(math-test-suite cdpl-math-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Math" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/math-test-suite")
