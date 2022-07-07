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


# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.
MACRO(CONFIGURE_FILES SRC_DIR DEST_DIR)
    FILE(GLOB TEMPLATE_FILES RELATIVE "${SRC_DIR}" "${SRC_DIR}/*.in")

    FOREACH(TEMPLATE_FILE ${TEMPLATE_FILES})
        SET(SRC_TEMPLATE_PATH "${SRC_DIR}/${TEMPLATE_FILE}")

        IF(NOT IS_DIRECTORY "${SRC_TEMPLATE_PATH}")
	  GET_FILENAME_COMPONENT(DEST_FILE_NAME "${TEMPLATE_FILE}" NAME_WLE)
	  SET(DEST_FILE_PATH "${DEST_DIR}/${DEST_FILE_NAME}")
          #MESSAGE(STATUS "Configuring file ${SRC_TEMPLATE_PATH} and write it to ${DEST_FILE_PATH}")
          CONFIGURE_FILE("${SRC_TEMPLATE_PATH}" "${DEST_FILE_PATH}" @ONLY)
        ENDIF(NOT IS_DIRECTORY "${SRC_TEMPLATE_PATH}")
    ENDFOREACH(TEMPLATE_FILE)
ENDMACRO(CONFIGURE_FILES)


IF(SPHINX_FOUND)
  SET(SPHINX_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
  SET(SPHINX_PROC_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/source")

  ADD_CUSTOM_TARGET(sphinx-doc "${SPHINX_EXECUTABLE}"
    -q -b html
    -c "${SPHINX_PROC_SOURCE_DIR}"
    "${SPHINX_PROC_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/html"
    COMMENT "Building HTML documentation with Sphinx")

  FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CopySources.cmake"
    "FILE(COPY ${SPHINX_SOURCE_DIR}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    PATTERN *.in EXCLUDE PATTERN *~ EXCLUDE)")

  ADD_CUSTOM_TARGET(copy-sphinx-sources 
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopySources.cmake"
    COMMENT "Preprocessing Sphinx source files")

  CONFIGURE_FILES("${SPHINX_SOURCE_DIR}" "${SPHINX_PROC_SOURCE_DIR}")

  ADD_DEPENDENCIES(sphinx-doc copy-sphinx-sources)

  IF(DOXYGEN_EXECUTABLE)
    ADD_CUSTOM_COMMAND(TARGET sphinx-doc POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_BINARY_DIR}/../C++-API/html" "${CMAKE_CURRENT_BINARY_DIR}/html/cxx_api_doc"
      COMMENT "Copying C++-API documentation to Sphinx output directory")

    ADD_CUSTOM_COMMAND(TARGET sphinx-doc POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_BINARY_DIR}/../Python-API/html" "${CMAKE_CURRENT_BINARY_DIR}/html/python_api_doc"
      COMMENT "Copying Python-API documentation to Sphinx output directory")

    ADD_DEPENDENCIES(sphinx-doc c++-api-doc)
    ADD_DEPENDENCIES(sphinx-doc python-api-doc)
  ENDIF(DOXYGEN_EXECUTABLE)

  INSTALL(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "${CDPKIT_DOC_INSTALL_DIR}"
          COMPONENT Documentation OPTIONAL)
ENDIF(SPHINX_FOUND)
