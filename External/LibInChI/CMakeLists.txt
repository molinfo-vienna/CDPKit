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

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB inchi_LIB_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

IF(CMAKE_COMPILER_IS_GNUCC AND UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
ENDIF(CMAKE_COMPILER_IS_GNUCC AND UNIX)

ADD_LIBRARY(inchi-static STATIC ${inchi_LIB_SRCS})
SET_TARGET_PROPERTIES(inchi-static PROPERTIES COMPILE_DEFINITIONS "TARGET_API_LIB")

#INSTALL(TARGETS inchi
#  RUNTIME DESTINATION ${CDPKIT_EXECUTABLE_INSTALL_DIR} COMPONENT CDPLSharedLibraries
#  LIBRARY DESTINATION ${CDPKIT_LIBRARY_INSTALL_DIR} COMPONENT CDPLSharedLibraries
#  ARCHIVE DESTINATION ${CDPKIT_LIBRARY_INSTALL_DIR} COMPONENT CDPLStaticLibraries
#)
