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


set(DOC_FILE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(PROC_DOC_FILE_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Source")
  
configure_file(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
configure_file(CopyDocSourceFiles.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CopyDocSourceFiles.cmake" @ONLY)
configure_file(GenDocSourceFiles.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/GenDocSourceFiles.cmake" @ONLY)
configure_file(PostProcHTMLFiles.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/PostProcHTMLFiles.cmake" @ONLY)

add_custom_target(gen-c++-api-doc-db
  "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/ExtractCXXAPIDocBlocks.py" 
  "${CDPL_CXX_API_DOC_BUILD_DIR}/xml/" "${CMAKE_CURRENT_BINARY_DIR}/cxx_api_doc.db"
  COMMENT "-- Extracting CDPL C++ API documentation blocks..."
  DEPENDS c++-api-doc-xml)

add_custom_target(gen-python-api-doc-sources
  ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/GenDocSourceFiles.cmake"
  COMMENT "-- Generating CDPL Python API documentation source files..."
  DEPENDS gen-c++-api-doc-db)

add_custom_target(copy-python-api-doc-sources
  ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopyDocSourceFiles.cmake"
  COMMENT "-- Copying CDPL Python API documentation source files...")

add_custom_target(python-api-doc
  ${CMAKE_COMMAND} -E rm -r -f "${CMAKE_CURRENT_BINARY_DIR}/html"
  COMMAND "${DOXYGEN_EXECUTABLE}" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "-- Generating CDPL Python API documentation HTML files..."
  DEPENDS copy-python-api-doc-sources)

add_custom_command(TARGET python-api-doc POST_BUILD
  COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/PostProcHTMLFiles.cmake"
  COMMENT "-- Post-processing CDPL Python API documentation HTML files...")
