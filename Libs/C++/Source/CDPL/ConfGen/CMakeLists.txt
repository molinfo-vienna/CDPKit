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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" "${CDPKIT_EXTERNAL_DIR}")

SET(DATA_FILES
    TorsionLibrary.xml
    FallbackTorsionLibrary.xml
   )

IF(MSVC)
  CONFIGURE_FILE(FragmentLibraryData.rc.in FragmentLibraryData.rc @ONLY)
ELSE()
  SET(DATA_FILES ${DATA_FILES} FragmentLibrary.cfl)
ENDIF()
    
FOREACH(DATA_FILE ${DATA_FILES})
  ADD_CUSTOM_COMMAND(OUTPUT "${DATA_FILE}.str"
    COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
    "${CDPKIT_BUILTIN_DATA_DIR}/ConfGen/${DATA_FILE}" 
    "${DATA_FILE}.str"
    DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/ConfGen/${DATA_FILE}"
    COMMENT "-- Processing ${DATA_FILE}..."
    )
  SET(DATA_FILE_STRINGS "${DATA_FILE_STRINGS}" "${DATA_FILE}.str") 
ENDFOREACH(DATA_FILE)

ADD_CUSTOM_TARGET(gen-confgen-data-files DEPENDS ${DATA_FILE_STRINGS})

SET(cdpl-confgen_LIB_SRCS
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

    SubstituentBulkinessCalculator.cpp
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

IF(MSVC)
  SET(cdpl-confgen_LIB_SRCS ${cdpl-confgen_LIB_SRCS} "${CMAKE_CURRENT_BINARY_DIR}/FragmentLibraryData.rc")
ENDIF()
  
LINK_LIBRARIES(${Boost_IOSTREAMS_LIBRARY})

IF(NOT CDPL_PYPI_PACKAGE_BUILD)
  ADD_LIBRARY(cdpl-confgen-static STATIC ${cdpl-confgen_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)
  ADD_DEPENDENCIES(cdpl-confgen-static gen-confgen-data-files)
  
  SET_TARGET_PROPERTIES(cdpl-confgen-static PROPERTIES 
    OUTPUT_NAME cdpl-confgen
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_CONFGEN_STATIC_LINK")

  TARGET_LINK_LIBRARIES(cdpl-confgen-static cdpl-base-static cdpl-chem-static cdpl-molprop-static cdpl-math-static
    cdpl-util-static cdpl-forcefield-static)

  INSTALL(TARGETS cdpl-confgen-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
ENDIF(NOT CDPL_PYPI_PACKAGE_BUILD)

ADD_LIBRARY(cdpl-confgen-shared SHARED ${cdpl-confgen_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)
ADD_DEPENDENCIES(cdpl-confgen-shared gen-confgen-data-files)

TARGET_LINK_LIBRARIES(cdpl-confgen-shared cdpl-chem-shared cdpl-molprop-shared cdpl-base-shared cdpl-math-shared
  cdpl-util-shared cdpl-forcefield-shared)

SET_TARGET_PROPERTIES(cdpl-confgen-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-confgen
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

IF(WIN32)
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-confgen.dll")
ELSEIF(APPLE)
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-confgen.dylib")
ELSE()            
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-confgen.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

INSTALL(TARGETS cdpl-confgen-shared
  RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
  LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
  ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

IF(CDPL_CXX_UNIT_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(CDPL_CXX_UNIT_TESTS_ENABLED)
