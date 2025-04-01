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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

set(PARAMETER_FILES
    MMFFANG.PAR
    MMFFAROM.PAR
    MMFFBNDK.PAR
    MMFFBOND.PAR
    MMFFCHG.PAR
    MMFFDEF.PAR
    MMFFDFSB.PAR
    MMFFHDEF.PAR
    MMFFOOP.PAR
    MMFFPBCI.PAR
    MMFFPROP.PAR
    MMFFSMTP.PAR
    MMFFSOOP.PAR
    MMFFSXOOP.PAR
    MMFFSTBN.PAR
    MMFFSTOR.PAR
    MMFFSRTOR.PAR
    MMFFSYMB.PAR
    MMFFTOR.PAR
    MMFFVDW.PAR    
    MMFFFCHG.PAR    
   )

foreach(PARAM_FILE ${PARAMETER_FILES})
  add_custom_command(OUTPUT "${PARAM_FILE}.str"
    COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
    "${CDPKIT_BUILTIN_DATA_DIR}/ForceField/${PARAM_FILE}" 
    "${PARAM_FILE}.str"
    DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/ForceField/${PARAM_FILE}"
    COMMENT "-- Processing ${PARAM_FILE}..."
    )
  set(PARAMETER_FILE_STRINGS "${PARAMETER_FILE_STRINGS}" "${PARAM_FILE}.str") 
endforeach(PARAM_FILE)

add_custom_target(gen-forcefield-data-files DEPENDS ${PARAMETER_FILE_STRINGS})

set(cdpl-forcefield_LIB_SRCS
    ${PARAMETER_FILE_STRINGS}

    Exceptions.cpp
    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp

    AtomPropertyFunctions.cpp
    AtomUFFTypeFunction.cpp
    
    BondPropertyFunctions.cpp

    MolecularGraphPropertyFunctions.cpp
    MolecularGraphMMFF94AtomTypesFunction.cpp
    MolecularGraphMMFF94BondTypeIndicesFunction.cpp 
    MolecularGraphMMFF94AromaticRingSetFunctions.cpp 
    MolecularGraphMMFF94AtomChargesFunction.cpp
    MolecularGraphUFFAtomTypesFunction.cpp
    
    UFFAtomTypePropertyTable.cpp

    MMFF94AtomTyper.cpp
    MMFF94BondTyper.cpp
    MMFF94ChargeCalculator.cpp
    MMFF94AromaticSSSRSubset.cpp

    MMFF94InteractionData.cpp

    MMFF94BondStretchingInteractionParameterizer.cpp
    MMFF94AngleBendingInteractionParameterizer.cpp
    MMFF94StretchBendInteractionParameterizer.cpp
    MMFF94OutOfPlaneBendingInteractionParameterizer.cpp
    MMFF94TorsionInteractionParameterizer.cpp
    MMFF94VanDerWaalsInteractionParameterizer.cpp
    MMFF94ElectrostaticInteractionParameterizer.cpp
    MMFF94InteractionParameterizer.cpp

    MMFF94ParameterData.cpp
    MMFF94SymbolicAtomTypePatternTable.cpp
    MMFF94HeavyToHydrogenAtomTypeMap.cpp
    MMFF94SymbolicToNumericAtomTypeMap.cpp
    MMFF94AromaticAtomTypeDefinitionTable.cpp
    MMFF94AtomTypePropertyTable.cpp
    MMFF94BondChargeIncrementTable.cpp
    MMFF94PartialBondChargeIncrementTable.cpp
    MMFF94FormalAtomChargeDefinitionTable.cpp
    MMFF94PrimaryToParameterAtomTypeMap.cpp
    MMFF94AngleBendingParameterTable.cpp
    MMFF94BondStretchingParameterTable.cpp
    MMFF94BondStretchingRuleParameterTable.cpp
    MMFF94StretchBendParameterTable.cpp
    MMFF94DefaultStretchBendParameterTable.cpp
    MMFF94OutOfPlaneBendingParameterTable.cpp
    MMFF94TorsionParameterTable.cpp
    MMFF94VanDerWaalsParameterTable.cpp

    UtilityFunctions.cpp
    DataIOUtilities.cpp
   )

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-forcefield-static STATIC ${cdpl-forcefield_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)
  add_dependencies(cdpl-forcefield-static gen-forcefield-data-files)
  
  set_target_properties(cdpl-forcefield-static PROPERTIES 
    OUTPUT_NAME cdpl-forcefield
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_FORCEFIELD_STATIC_LINK")

  target_link_libraries(cdpl-forcefield-static cdpl-base-static cdpl-chem-static cdpl-molprop-static cdpl-math-static Boost::iostreams)
  target_include_directories(cdpl-forcefield-static
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

  install(TARGETS cdpl-forcefield-static EXPORT ExportedTargets
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-forcefield-shared SHARED ${cdpl-forcefield_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)
add_dependencies(cdpl-forcefield-shared gen-forcefield-data-files)

target_link_libraries(cdpl-forcefield-shared PUBLIC cdpl-base-shared cdpl-chem-shared cdpl-molprop-shared cdpl-math-shared)
target_link_libraries(cdpl-forcefield-shared PRIVATE Boost::iostreams)

target_include_directories(cdpl-forcefield-shared
  PUBLIC
  "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
  "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

set_target_properties(cdpl-forcefield-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-forcefield
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-forcefield.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-forcefield.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-forcefield.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-forcefield-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-forcefield-shared EXPORT ExportedTargets
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)
