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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" "${CDPKIT_EXTERNAL_DIR}")

set(DATA_FILES
    TorsionLibrary.xml
    FallbackTorsionLibrary.xml
   )

if(MSVC)
  configure_file(FragmentLibraryData.rc.in "${CMAKE_CURRENT_BINARY_DIR}/FragmentLibraryData.rc" @ONLY)
else()
  set(DATA_FILES ${DATA_FILES} FragmentLibrary.cfl)
endif()
    
foreach(DATA_FILE ${DATA_FILES})
  add_custom_command(OUTPUT "${DATA_FILE}.str"
    COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
    "${CDPKIT_BUILTIN_DATA_DIR}/ConfGen/${DATA_FILE}" 
    "${DATA_FILE}.str"
    DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/ConfGen/${DATA_FILE}"
    COMMENT "-- Processing ${DATA_FILE}..."
    )
  set(DATA_FILE_STRINGS "${DATA_FILE_STRINGS}" "${DATA_FILE}.str") 
endforeach(DATA_FILE)

add_custom_target(gen-confgen-data-files DEPENDS ${DATA_FILE_STRINGS})

set(cdpl-confgen_LIB_SRCS
    ${DATA_FILE_STRINGS}

    DataFormat.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp

    DGConstraintGenerator.cpp
    DGStructureGenerator.cpp
    CanonicalFragment.cpp
    FragmentLibraryEntry.cpp
    FragmentLibrary.cpp
    FragmentLibraryData.cpp
    TorsionLibrary.cpp
    TorsionRule.cpp
    TorsionCategory.cpp
    TorsionRuleMatch.cpp
    TorsionRuleMatcher.cpp
    RMSDConformerSelector.cpp
    TorsionDriver.cpp
    TorsionDriverImpl.cpp

    DGStructureGeneratorSettings.cpp
    DGConstraintGeneratorSettings.cpp
    ConformerGeneratorSettings.cpp
    StructureGeneratorSettings.cpp
    TorsionDriverSettings.cpp
    FragmentConformerGeneratorSettings.cpp
    FragmentAssemblerSettings.cpp
    SettingsPresets.cpp

    CFLFragmentLibraryEntryReader.cpp
    CFLFragmentLibraryEntryWriter.cpp
    CFLDataReader.cpp
    CFLMoleculeReader.cpp
    TorsionLibraryDataReader.cpp
    TorsionLibraryDataWriter.cpp

    FallbackTorsionLibrary.cpp

    FragmentTreeNode.cpp
    FragmentTree.cpp

    FragmentConformerCache.cpp

    ExtendedConnectivityCalculator.cpp
    MMFF94BondLengthTable.cpp

    ForceFieldInteractionMask.cpp

    ControlParameterFunctions.cpp
    BondFunctions.cpp
    MolecularGraphFunctions.cpp
    MoleculeFunctions.cpp
    UtilityFunctions.cpp

    StructureGenerator.cpp
    ConformerGenerator.cpp
    ConformerGeneratorImpl.cpp
    FragmentConformerGenerator.cpp
    FragmentConformerGeneratorImpl.cpp
    FragmentLibraryGenerator.cpp
    FragmentAssembler.cpp
    FragmentAssemblerImpl.cpp
   )

if(MSVC)
  set(cdpl-confgen_LIB_SRCS ${cdpl-confgen_LIB_SRCS} "${CMAKE_CURRENT_BINARY_DIR}/FragmentLibraryData.rc")
endif()
  
link_libraries(${Boost_IOSTREAMS_LIBRARY})

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-confgen-static STATIC ${cdpl-confgen_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)
  add_dependencies(cdpl-confgen-static gen-confgen-data-files)
  
  set_target_properties(cdpl-confgen-static PROPERTIES 
    OUTPUT_NAME cdpl-confgen
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_CONFGEN_STATIC_LINK")

  target_link_libraries(cdpl-confgen-static cdpl-base-static cdpl-chem-static cdpl-molprop-static cdpl-math-static
    cdpl-util-static cdpl-forcefield-static)

  install(TARGETS cdpl-confgen-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-confgen-shared SHARED ${cdpl-confgen_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)
add_dependencies(cdpl-confgen-shared gen-confgen-data-files)

target_link_libraries(cdpl-confgen-shared cdpl-chem-shared cdpl-molprop-shared cdpl-base-shared cdpl-math-shared
  cdpl-util-shared cdpl-forcefield-shared)

set_target_properties(cdpl-confgen-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-confgen
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-confgen.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-confgen.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-confgen.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-confgen-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-confgen-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)
