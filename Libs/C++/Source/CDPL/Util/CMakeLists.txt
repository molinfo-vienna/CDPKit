# -*- mode: CMake -*-

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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(cdpl-util_LIB_SRCS
    BronKerboschAlgorithm.cpp
   )

LINK_LIBRARIES(${Boost_SYSTEM_LIBRARY})

IF(Boost_FILESYSTEM_FOUND)
   SET(cdpl-util_LIB_SRCS
      ${cdpl-util_LIB_SRCS}
      FileRemover.cpp
      FileFunctions.cpp
      )	  

   LINK_LIBRARIES(${Boost_FILESYSTEM_LIBRARY})
ENDIF(Boost_FILESYSTEM_FOUND)

IF(Boost_IOSTREAMS_FOUND)
   LINK_LIBRARIES(${Boost_IOSTREAMS_LIBRARY})
ENDIF(Boost_IOSTREAMS_FOUND)

ADD_LIBRARY(cdpl-util-static STATIC ${cdpl-util_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-util-static cdpl-base-static)

SET_TARGET_PROPERTIES(cdpl-util-static PROPERTIES 
                      OUTPUT_NAME cdpl-util
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

INSTALL(TARGETS cdpl-util-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-util-shared SHARED ${cdpl-util_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-util-shared cdpl-base-shared)

SET_TARGET_PROPERTIES(cdpl-util-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                      OUTPUT_NAME cdpl-util
		      CLEAN_DIRECT_OUTPUT 1
		      INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
		      )

IF(WIN32)
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-util.dll")
ELSEIF(APPLE)
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-util.dylib")
ELSE()			
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-util.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
	       @ONLY
	       )

INSTALL(TARGETS cdpl-util-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
	LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
	ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
	)

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

IF(CDPL_CXX_UNIT_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(CDPL_CXX_UNIT_TESTS_ENABLED)
