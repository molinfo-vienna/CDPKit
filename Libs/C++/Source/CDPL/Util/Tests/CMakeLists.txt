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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(test-suite_SRCS
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
    DGCoordinatesGeneratorTest.cpp
    FoldBitSetFunctionTest.cpp
   )

set(CMAKE_BUILD_TYPE "Debug")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

add_executable(util-test-suite ${test-suite_SRCS})

target_link_libraries(util-test-suite cdpl-util-shared Boost::unit_test_framework)

ADD_TEST("CDPL::Util" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/util-test-suite")
