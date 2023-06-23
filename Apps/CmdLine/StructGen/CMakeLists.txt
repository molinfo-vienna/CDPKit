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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${APPS_SOURCE_DIR}")

SET(structgen_SRCS
    Main.cpp
    StructGenImpl.cpp
   )

ADD_EXECUTABLE(structgen ${structgen_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

SET_TARGET_PROPERTIES(structgen PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

IF(WIN32)
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/structgen.exe")
ELSE()
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/structgen")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
	       @ONLY
	       )

TARGET_LINK_LIBRARIES(structgen cmdline-static cdpl-util-shared cdpl-base-shared cdpl-chem-shared 
		      cdpl-confgen-shared Threads::Threads)

INSTALL(TARGETS structgen DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT Applications)
