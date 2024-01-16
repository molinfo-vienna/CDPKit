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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
endforeach(PYTHON_FILE)

set(forcefield_MOD_SRCS
    Module.cpp
 
    MolecularGraphPropertyExport.cpp 
    AtomPropertyExport.cpp 
    BondPropertyExport.cpp 
    InteractionTypeExport.cpp

    UFFAtomTypeExport.cpp
    UFFAtomTypePropertyTableExport.cpp
 
    MMFF94ParameterSetExport.cpp

    MMFF94AromaticSSSRSubsetExport.cpp
    MMFF94AtomTyperExport.cpp
    MMFF94BondTyperExport.cpp
    MMFF94ChargeCalculatorExport.cpp

    MMFF94EnergyCalculatorExport.cpp
    MMFF94GradientCalculatorExport.cpp

    MMFF94BondStretchingInteractionExport.cpp
    MMFF94AngleBendingInteractionExport.cpp
    MMFF94StretchBendInteractionExport.cpp
    MMFF94OutOfPlaneBendingInteractionExport.cpp
    MMFF94TorsionInteractionExport.cpp
    MMFF94VanDerWaalsInteractionExport.cpp
    MMFF94ElectrostaticInteractionExport.cpp

    MMFF94BondStretchingInteractionDataExport.cpp
    MMFF94AngleBendingInteractionDataExport.cpp
    MMFF94StretchBendInteractionDataExport.cpp
    MMFF94OutOfPlaneBendingInteractionDataExport.cpp
    MMFF94TorsionInteractionDataExport.cpp
    MMFF94VanDerWaalsInteractionDataExport.cpp
    MMFF94ElectrostaticInteractionDataExport.cpp
    MMFF94InteractionDataExport.cpp

    MMFF94BondStretchingInteractionParameterizerExport.cpp
    MMFF94AngleBendingInteractionParameterizerExport.cpp
    MMFF94StretchBendInteractionParameterizerExport.cpp
    MMFF94OutOfPlaneBendingInteractionParameterizerExport.cpp
    MMFF94TorsionInteractionParameterizerExport.cpp
    MMFF94VanDerWaalsInteractionParameterizerExport.cpp
    MMFF94ElectrostaticInteractionParameterizerExport.cpp
    MMFF94InteractionParameterizerExport.cpp

    MMFF94SymbolicAtomTypePatternTableExport.cpp
    MMFF94HeavyToHydrogenAtomTypeMapExport.cpp
    MMFF94SymbolicToNumericAtomTypeMapExport.cpp
    MMFF94AromaticAtomTypeDefinitionTableExport.cpp
    MMFF94AtomTypePropertyTableExport.cpp
    MMFF94FormalAtomChargeDefinitionTableExport.cpp
    MMFF94BondChargeIncrementTableExport.cpp
    MMFF94PartialBondChargeIncrementTableExport.cpp
    MMFF94PrimaryToParameterAtomTypeMapExport.cpp
    MMFF94BondStretchingParameterTableExport.cpp
    MMFF94BondStretchingRuleParameterTableExport.cpp
    MMFF94AngleBendingParameterTableExport.cpp
    MMFF94StretchBendParameterTableExport.cpp
    MMFF94DefaultStretchBendParameterTableExport.cpp
    MMFF94OutOfPlaneBendingParameterTableExport.cpp
    MMFF94TorsionParameterTableExport.cpp
    MMFF94VanDerWaalsParameterTableExport.cpp

    ElasticPotentialExport.cpp
    ElasticPotentialDataExport.cpp
   
    UtilityFunctionExport.cpp 
    MMFF94EnergyFunctionExport.cpp 
    MMFF94GradientFunctionExport.cpp
    ElasticPotentialFunctionExport.cpp
    AtomFunctionExport.cpp 
    BondFunctionExport.cpp 
    MolecularGraphFunctionExport.cpp 

    FunctionWrapperExport.cpp

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
    ExceptionTranslatorRegistration.cpp
   )

add_library(_forcefield MODULE ${forcefield_MOD_SRCS})

target_link_libraries(_forcefield cdpl-forcefield-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_forcefield PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_forcefield PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ForceField/_forcefield.pyd")
else(WIN32)
  set_target_properties(_forcefield PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ForceField/_forcefield.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ForceField" COMPONENT CDPLPythonModules)
install(TARGETS _forcefield DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ForceField" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
