# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    MMFF94GradientFunctionsTest.cpp
    MMFF94GradientCalculatorTest.cpp

    OptimolLogReader.cpp
    TestUtils.cpp
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(forcefield-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(forcefield-test-suite cdpl-forcefield-shared cdpl-chem-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::ForceField" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/forcefield-test-suite")
