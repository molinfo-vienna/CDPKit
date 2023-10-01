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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" "${CDPKIT_EXTERNAL_DIR}/MessagePack" "${CDPKIT_EXTERNAL_DIR}/MMTF")

if(MSVC)
  configure_file(ResidueDictionaryStructureData.rc.in "${CMAKE_CURRENT_BINARY_DIR}/ResidueDictionaryStructureData.rc" @ONLY)
else()
  add_custom_command(OUTPUT ResidueDictionaryStructureData.cdf.str
    COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
    "${CDPKIT_BUILTIN_DATA_DIR}/Biomol/ResidueDictionaryStructureData.cdf" 
    "ResidueDictionaryStructureData.cdf.str"
    DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/Biomol/ResidueDictionaryStructureData.cdf" 
    COMMENT "-- Processing residue dictionary structure data..."
    )
  add_custom_target(gen-biomol-data-files DEPENDS ResidueDictionaryStructureData.cdf.str)
endif()

set(cdpl-biomol_LIB_SRCS
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

if(MSVC)
  set(cdpl-biomol_LIB_SRCS ${cdpl-biomol_LIB_SRCS} "${CMAKE_CURRENT_BINARY_DIR}/ResidueDictionaryStructureData.rc")
else()
  set(cdpl-biomol_LIB_SRCS ${cdpl-biomol_LIB_SRCS} ResidueDictionaryStructureData.cdf.str)
endif()
 
link_libraries(${Boost_IOSTREAMS_LIBRARY})

if(WIN32)
  if(MINGW)
    link_libraries(libwsock32.a)
  elseif(MSVC)
    link_libraries(ws2_32)
  endif()
endif(WIN32)

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-biomol-static STATIC ${cdpl-biomol_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  if(NOT MSVC)
    add_dependencies(cdpl-biomol-static gen-biomol-data-files)
  endif()
  
  set_target_properties(cdpl-biomol-static PROPERTIES 
    OUTPUT_NAME cdpl-biomol
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_BIOMOL_STATIC_LINK")

  target_link_libraries(cdpl-biomol-static cdpl-chem-static cdpl-molprop-static cdpl-math-static cdpl-util-static cdpl-base-static)

  install(TARGETS cdpl-biomol-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-biomol-shared SHARED ${cdpl-biomol_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

if(NOT MSVC)
  add_dependencies(cdpl-biomol-shared gen-biomol-data-files)
endif()

target_link_libraries(cdpl-biomol-shared cdpl-chem-shared cdpl-molprop-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared)

set_target_properties(cdpl-biomol-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-biomol
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-biomol.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-biomol.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-biomol.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-biomol-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-biomol-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)
