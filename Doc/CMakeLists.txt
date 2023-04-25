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
  ADD_SUBDIRECTORY(Doxygen)
ENDIF(DOXYGEN_EXECUTABLE)

IF(SPHINX_FOUND)
  ADD_SUBDIRECTORY(Sphinx)

  ADD_CUSTOM_TARGET(doc ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_BINARY_DIR}/Sphinx/html" "${CMAKE_CURRENT_BINARY_DIR}/html")

  IF(DOXYGEN_EXECUTABLE)
    ADD_CUSTOM_COMMAND(TARGET doc POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_BINARY_DIR}/Doxygen/C++-API/html" "${CMAKE_CURRENT_BINARY_DIR}/html/cpp_api")

    ADD_CUSTOM_COMMAND(TARGET doc POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_BINARY_DIR}/Doxygen/Python-API/html" "${CMAKE_CURRENT_BINARY_DIR}/html/python_api")

    ADD_DEPENDENCIES(doc c++-api-doc python-api-doc sphinx-doc)
  ENDIF(DOXYGEN_EXECUTABLE)

  INSTALL(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "${CDPKIT_DOC_INSTALL_DIR}"
    COMPONENT Documentation OPTIONAL)
ENDIF(SPHINX_FOUND)
