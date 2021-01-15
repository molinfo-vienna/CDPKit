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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" "${CDPKIT_EXTERNAL_DIR}/MessagePack" "${CDPKIT_EXTERNAL_DIR}/MMTF")

ADD_CUSTOM_COMMAND(OUTPUT "ResidueDictionaryStructureData.cdf.str"
		   COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
		   "${CDPKIT_BUILTIN_DATA_DIR}/Biomol/ResidueDictionaryStructureData.cdf" 
		   "ResidueDictionaryStructureData.cdf.str"
		   DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/Biomol/ResidueDictionaryStructureData.cdf" 
		   COMMENT "-- Processing residue dictionary structure data, please wait..."
		   )

SET(cdpl-biomol_LIB_SRCS
    ResidueDictionaryStructureData.cdf.str

    PDBData.cpp
    ResidueDictionaryData.cpp
    ResidueDictionary.cpp
    ResidueList.cpp

    AtomProperty.cpp
    MolecularGraphProperty.cpp
    AtomPropertyDefault.cpp
    MolecularGraphPropertyDefault.cpp
    DataFormat.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp

    PDBDataReader.cpp
    PDBDataWriter.cpp
    PDBMoleculeReader.cpp
    PDBMolecularGraphWriter.cpp
    CDFDataReader.cpp
    CDFDataWriter.cpp
    MMTFDataReader.cpp
    MMTFDataWriter.cpp
    MMTFMoleculeReader.cpp
    MMTFMolecularGraphWriter.cpp
    
    HierarchyViewNode.cpp
    HierarchyViewModel.cpp
    HierarchyViewChain.cpp
    HierarchyView.cpp

    AtomPropertyFunctions.cpp
    MolecularGraphPropertyFunctions.cpp
    ControlParameterFunctions.cpp

    AtomUtilityFunctions.cpp
    MolecularGraphUtilityFunctions.cpp
    MoleculeUtilityFunctions.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

IF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
   LINK_LIBRARIES(${Boost_FILESYSTEM_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
ENDIF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)

IF(WIN32 AND MINGW)		     
   LINK_LIBRARIES(libwsock32.a)
ENDIF(WIN32 AND MINGW)

ADD_LIBRARY(cdpl-biomol-static STATIC ${cdpl-biomol_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-biomol-static PROPERTIES 
                      OUTPUT_NAME cdpl-biomol
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_BIOMOL_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-biomol-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static)

INSTALL(TARGETS cdpl-biomol-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-biomol-shared SHARED ${cdpl-biomol_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-biomol-shared cdpl-chem-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-biomol-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Biomol
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-biomol-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-biomol
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(WIN32)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-biomol.dll")
  ELSE()			
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-biomol.so")
  ENDIF(WIN32)

  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake"
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-biomol-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
