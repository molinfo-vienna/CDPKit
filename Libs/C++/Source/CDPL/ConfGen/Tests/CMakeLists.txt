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
    )

set(CMAKE_BUILD_TYPE "Debug")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

add_executable(confgen-test-suite ${test-suite_SRCS})

target_link_libraries(confgen-test-suite cdpl-confgen-shared cdpl-chem-shared cdpl-forcefield-shared Boost::unit_test_framework)

ADD_TEST("CDPL::ConfGen" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/confgen-test-suite")
