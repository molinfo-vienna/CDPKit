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

set(confgen_MOD_SRCS
    Module.cpp

    ForceFieldTypeExport.cpp
    FragmentTypeExport.cpp
    ReturnCodeExport.cpp
    NitrogenEnumerationModeExport.cpp
    ConformerSamplingModeExport.cpp
    StructureGenerationModeExport.cpp
    DataFormatExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 

    DGConstraintGeneratorExport.cpp
    DGConstraintGeneratorSettingsExport.cpp
    DGStructureGeneratorExport.cpp
    DGStructureGeneratorSettingsExport.cpp
    StructureGeneratorExport.cpp
    ConformerGeneratorExport.cpp
    FragmentConformerGeneratorExport.cpp
    FragmentLibraryGeneratorExport.cpp
    FragmentAssemblerExport.cpp
    CanonicalFragmentExport.cpp
    FragmentLibraryEntryExport.cpp
    FragmentLibraryExport.cpp
    ConformerDataExport.cpp
    TorsionRuleExport.cpp
    TorsionCategoryExport.cpp
    TorsionLibraryExport.cpp
    TorsionRuleMatchExport.cpp
    TorsionRuleMatcherExport.cpp
    TorsionDriverExport.cpp
    TorsionDriverSettingsExport.cpp
    RMSDConformerSelectorExport.cpp
    StructureGeneratorSettingsExport.cpp
    ConformerGeneratorSettingsExport.cpp
    FragmentConformerGeneratorSettingsExport.cpp
    FragmentAssemblerSettingsExport.cpp
    
    CFLMoleculeReaderExport.cpp
    CFLMoleculeInputHandlerExport.cpp 

    BondFunctionExport.cpp
    MolecularGraphFunctionExport.cpp
    MoleculeFunctionExport.cpp
    ControlParameterFunctionExport.cpp 

    FunctionWrapperExport.cpp
   
    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
    )    

add_library(_confgen MODULE ${confgen_MOD_SRCS})

target_link_libraries(_confgen cdpl-confgen-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_confgen PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_confgen PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ConfGen/_confgen.pyd")
else(WIN32)
  set_target_properties(_confgen PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ConfGen/_confgen.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ConfGen" COMPONENT CDPLPythonModules)
install(TARGETS _confgen DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/ConfGen" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
