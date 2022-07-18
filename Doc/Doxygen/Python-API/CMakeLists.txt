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

IF(DOXYGEN_EXECUTABLE)
  SET(DOC_FILE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
  SET(PROC_DOC_FILE_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Source")

  CONFIGURE_FILE(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
  CONFIGURE_FILE(CopySources.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CopySources.cmake" @ONLY)

  ADD_CUSTOM_TARGET(copy-python-api-doc-sources 
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopySources.cmake"
    COMMENT "Preprocessing Python API documentation source files")

  ADD_CUSTOM_TARGET(python-api-doc "${DOXYGEN_EXECUTABLE}" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

  ADD_DEPENDENCIES(python-api-doc copy-python-api-doc-sources)
ENDIF(DOXYGEN_EXECUTABLE)
