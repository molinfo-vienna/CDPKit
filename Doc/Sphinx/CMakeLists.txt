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

# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.
MACRO(CONFIGURE_FILES SRC_DIR DEST_DIR)
  FILE(GLOB TEMPLATE_FILES RELATIVE "${SRC_DIR}" "${SRC_DIR}/*.in")

  FOREACH(TEMPLATE_FILE ${TEMPLATE_FILES})
    SET(SRC_TEMPLATE_PATH "${SRC_DIR}/${TEMPLATE_FILE}")

    IF(NOT IS_DIRECTORY "${SRC_TEMPLATE_PATH}")
      GET_FILENAME_COMPONENT(DEST_FILE_NAME "${TEMPLATE_FILE}" NAME_WLE)
      SET(DEST_FILE_PATH "${DEST_DIR}/${DEST_FILE_NAME}")
      MESSAGE(STATUS "Configuring file ${SRC_TEMPLATE_PATH} and write it to ${DEST_FILE_PATH}")
      CONFIGURE_FILE("${SRC_TEMPLATE_PATH}" "${DEST_FILE_PATH}" @ONLY)
    ENDIF(NOT IS_DIRECTORY "${SRC_TEMPLATE_PATH}")
  ENDFOREACH(TEMPLATE_FILE)
ENDMACRO(CONFIGURE_FILES)

IF(SPHINX_FOUND)
  SET(SPHINX_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
  SET(SPHINX_PROC_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Source")

  ADD_CUSTOM_TARGET(sphinx-doc "${SPHINX_EXECUTABLE}"
    -q -b html
    -c "${SPHINX_PROC_SOURCE_DIR}"
    "${SPHINX_PROC_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/html"
    COMMENT "-- Running Sphinx...")

  FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CopySphinxSources.cmake"
    "FILE(COPY \"${SPHINX_SOURCE_DIR}\" DESTINATION \"${CMAKE_CURRENT_BINARY_DIR}\" PATTERN *.in EXCLUDE PATTERN *~ EXCLUDE)")

  ADD_CUSTOM_TARGET(copy-sphinx-sources 
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopySphinxSources.cmake"
    COMMENT "-- Copying Sphinx source files...")

  FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CopyExampleSourceFiles.cmake"
    "FILE(GLOB SOURCE_FILES \"${CDPKIT_EXAMPLES_DIR}/C++/*.cpp\" \"${CDPKIT_EXAMPLES_DIR}/Python/*.py\")\n"
    "FILE(COPY \$\{SOURCE_FILES\} DESTINATION \"${SPHINX_PROC_SOURCE_DIR}/examples\")")

  ADD_CUSTOM_TARGET(copy-example-files 
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopyExampleSourceFiles.cmake"
    COMMENT "-- Copying example source code files...")

  ADD_DEPENDENCIES(sphinx-doc copy-sphinx-sources copy-example-files)
  
  CONFIGURE_FILES("${SPHINX_SOURCE_DIR}" "${SPHINX_PROC_SOURCE_DIR}")
ENDIF(SPHINX_FOUND)
