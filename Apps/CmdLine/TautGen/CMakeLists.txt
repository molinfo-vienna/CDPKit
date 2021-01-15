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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${APPS_SOURCE_DIR}")

SET(tautgen_SRCS
    Main.cpp
    TautGenImpl.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

ADD_EXECUTABLE(tautgen ${tautgen_SRCS})

SET_TARGET_PROPERTIES(tautgen PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

IF(NOT APPLE)
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/tautgen")
  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
    @ONLY
    )

  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
ENDIF(NOT APPLE)

TARGET_LINK_LIBRARIES(tautgen cmdline-lib-static cdpl-util-shared cdpl-base-shared cdpl-chem-shared)

# Special non-dynamic version without external dependencies
#SET_TARGET_PROPERTIES(tautgen PROPERTIES LINK_FLAGS "-static")
#TARGET_LINK_LIBRARIES(tautgen cmdline-lib-static cdpl-util-static cdpl-base-static cdpl-chem-static pthread) 

#IF(Boost_IOSTREAMS_FOUND)
#  TARGET_LINK_LIBRARIES(tautgen ${Boost_IOSTREAMS_LIBRARY} z bz2) 
#ENDIF(Boost_IOSTREAMS_FOUND)

INSTALL(TARGETS tautgen DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
