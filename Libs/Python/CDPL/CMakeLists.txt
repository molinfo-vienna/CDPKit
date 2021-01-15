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

INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_DIRS}" "${CMAKE_CURRENT_SOURCE_DIR}")
ADD_COMPILE_DEFINITIONS(BOOST_BIND_GLOBAL_PLACEHOLDERS)

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
ENDFOREACH(PYTHON_FILE)

SET(cdpl_MOD_SRCS
    Module.cpp
    VersionInfoExport.cpp
    ConfigInfoExport.cpp
   )

ADD_LIBRARY(_cdpl MODULE ${cdpl_MOD_SRCS})
TARGET_LINK_LIBRARIES(_cdpl ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_cdpl PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_cdpl PROPERTIES SUFFIX ".pyd")
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_cdpl.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_cdpl PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_cdpl PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH1}")
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_cdpl.so")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_cdpl PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH1}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

IF(NOT APPLE)
  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
ENDIF(NOT APPLE)

INSTALL(TARGETS _cdpl DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL" COMPONENT CDPLPythonModules)
INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL" COMPONENT CDPLPythonModules)

ADD_SUBDIRECTORY(Base) 
ADD_SUBDIRECTORY(Math) 
ADD_SUBDIRECTORY(Util) 
ADD_SUBDIRECTORY(Chem) 
ADD_SUBDIRECTORY(Biomol) 
ADD_SUBDIRECTORY(Pharm) 
ADD_SUBDIRECTORY(ForceField) 
ADD_SUBDIRECTORY(ConfGen)
ADD_SUBDIRECTORY(Shape) 
ADD_SUBDIRECTORY(Grid) 
ADD_SUBDIRECTORY(Vis) 
