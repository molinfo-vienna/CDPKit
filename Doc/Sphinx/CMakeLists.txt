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

# Copy files from source directory to processed source directory, substituting any
# variables.  Create destination directory if it does not exist.
MACRO(CONFIGURE_FILES SRC_DIR DEST_DIR)
  file(GLOB_RECURSE TEMPLATE_FILES RELATIVE "${SRC_DIR}" "${SRC_DIR}/*.in")

  foreach(TEMPLATE_FILE ${TEMPLATE_FILES})
    set(SRC_FILE_PATH "${SRC_DIR}/${TEMPLATE_FILE}")
    get_filename_component(DEST_FILE_NAME "${TEMPLATE_FILE}" NAME_WLE)
    get_filename_component(DEST_FILE_DIR "${TEMPLATE_FILE}" DIRECTORY)
    set(DEST_FILE_PATH "${DEST_DIR}/${DEST_FILE_DIR}/${DEST_FILE_NAME}")
    #message(STATUS "Configuring file ${SRC_FILE_PATH}...")
    configure_file("${SRC_FILE_PATH}" "${DEST_FILE_PATH}" @ONLY)
  endforeach(TEMPLATE_FILE)
ENDMACRO(CONFIGURE_FILES)

if(SPHINX_FOUND)
  set(SPHINX_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
  set(SPHINX_PROC_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/ProcSource")
  set(SPHINX_BUILD_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Source")

  add_custom_command(OUTPUT "${SPHINX_SOURCE_DIR}/cdpl_python_tutorial/cdpl_python_tutorial.rst"
    COMMAND "jupyter" "nbconvert" "--to" "rst" "${SPHINX_SOURCE_DIR}/cdpl_python_tutorial/cdpl_python_tutorial.ipynb" 
    DEPENDS "${SPHINX_SOURCE_DIR}/cdpl_python_tutorial/cdpl_python_tutorial.ipynb"
    COMMENT "-- Converting CDPL Python tutorial Jupyter-notebook to RST format...")

  if(WIN32)
    add_custom_target(sphinx-doc
      ${CMAKE_COMMAND} -E rm -r -f "${CMAKE_CURRENT_BINARY_DIR}/html"
      COMMAND "${PYTHON_EXECUTABLE}" "${SPHINX_EXECUTABLE}"
      -q -a -n -E -b html
      -c "${SPHINX_BUILD_SOURCE_DIR}"
      "${SPHINX_BUILD_SOURCE_DIR}"
      "${CMAKE_CURRENT_BINARY_DIR}/html"
      COMMENT "-- Running Sphinx...")
  else()
    add_custom_target(sphinx-doc
      ${CMAKE_COMMAND} -E rm -r -f "${CMAKE_CURRENT_BINARY_DIR}/html"
      COMMAND "${SPHINX_EXECUTABLE}"
      -q -a -n -E -b html
      -c "${SPHINX_BUILD_SOURCE_DIR}"
      "${SPHINX_BUILD_SOURCE_DIR}"
      "${CMAKE_CURRENT_BINARY_DIR}/html"
      COMMENT "-- Running Sphinx...")
  endif(WIN32)

  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CopySphinxSourceFiles.cmake"
    "file(COPY \"${SPHINX_SOURCE_DIR}\" DESTINATION \"${CMAKE_CURRENT_BINARY_DIR}\" PATTERN *.in EXCLUDE PATTERN *~ EXCLUDE)\n"
    "file(COPY \"${SPHINX_PROC_SOURCE_DIR}/\" DESTINATION \"${SPHINX_BUILD_SOURCE_DIR}\")")

  add_custom_target(copy-sphinx-sources
    ${CMAKE_COMMAND} -E rm -r -f "${SPHINX_BUILD_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopySphinxSourceFiles.cmake"
    DEPENDS "${SPHINX_SOURCE_DIR}/cdpl_python_tutorial/cdpl_python_tutorial.rst"
    COMMENT "-- Copying Sphinx source files...")

  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CopyExampleSourceCodeFiles.cmake"
    "file(GLOB SOURCE_FILES \"${CDPKIT_EXAMPLES_DIR}/C++/*.cpp\" \"${CDPKIT_EXAMPLES_DIR}/Python/*.py\")\n"
    "file(COPY \$\{SOURCE_FILES\} DESTINATION \"${SPHINX_BUILD_SOURCE_DIR}/downloads\")")

  add_custom_target(copy-sphinx-example-files 
    ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopyExampleSourceCodeFiles.cmake"
    COMMENT "-- Copying example source code files...")

  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CopyGraphicsFiles.cmake"
    "file(COPY \"${CDPKIT_DOC_GRAPHICS_DIR}/\" DESTINATION \"${SPHINX_BUILD_SOURCE_DIR}/graphics\")")

  add_custom_target(copy-sphinx-graphics-files 
    ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/CopyGraphicsFiles.cmake"
    COMMENT "-- Copying graphics files...")

  add_dependencies(copy-sphinx-example-files copy-sphinx-sources)
  add_dependencies(copy-sphinx-graphics-files copy-sphinx-sources)
  add_dependencies(sphinx-doc copy-sphinx-sources copy-sphinx-example-files copy-sphinx-graphics-files)
  
  CONFIGURE_FILES("${SPHINX_SOURCE_DIR}" "${SPHINX_PROC_SOURCE_DIR}")
endif(SPHINX_FOUND)
