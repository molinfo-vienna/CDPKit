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


SET(CXX_API_DOC_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Source")

CONFIGURE_FILE(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
CONFIGURE_FILE(Doxyfile-xml.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-xml" @ONLY)
CONFIGURE_FILE(CopyDocSourceFiles.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CopyDocSourceFiles.cmake" @ONLY)

ADD_CUSTOM_TARGET(copy-c++-api-doc-sources
  ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopyDocSourceFiles.cmake"
  COMMENT "-- Copying CDPL C++ API documentation source files...")

ADD_CUSTOM_TARGET(c++-api-doc
  ${CMAKE_COMMAND} -E rm -r -f "${CMAKE_CURRENT_BINARY_DIR}/html"
  COMMAND "${DOXYGEN_EXECUTABLE}" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "-- Generating CDPL C++ API documentation HTML files...")
ADD_DEPENDENCIES(c++-api-doc copy-c++-api-doc-sources)

ADD_CUSTOM_TARGET(c++-api-doc-xml
  ${CMAKE_COMMAND} -E rm -r -f "${CMAKE_CURRENT_BINARY_DIR}/xml"
  COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-xml"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "-- Generating CDPL C++ API documentation XML files...")
ADD_DEPENDENCIES(c++-api-doc-xml copy-c++-api-doc-sources)
