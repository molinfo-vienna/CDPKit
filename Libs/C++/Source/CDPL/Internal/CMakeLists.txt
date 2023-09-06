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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

IF(CMAKE_COMPILER_IS_GNUCC AND UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF(CMAKE_COMPILER_IS_GNUCC AND UNIX)

SET(cdpl-internal_LIB_SRCS
    CDFDataWriterBase.cpp
    StringUtilities.cpp
    SHA1.cpp
    Time.cpp
   )

ADD_LIBRARY(cdpl-internal OBJECT ${cdpl-internal_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-internal PROPERTIES OUTPUT_NAME cdpl-internal CLEAN_DIRECT_OUTPUT 1)

IF(CDPL_CXX_UNIT_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(CDPL_CXX_UNIT_TESTS_ENABLED)
