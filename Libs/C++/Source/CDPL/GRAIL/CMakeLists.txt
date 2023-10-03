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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

set(cdpl-grail_LIB_SRCS
    AttributedGridProperty.cpp
    AttributedGridPropertyDefault.cpp
    DataFormat.cpp
    
    GeneralizedBellAtomDensity.cpp
    AtomDensityGridCalculator.cpp
    BuriednessScore.cpp
    BuriednessGridCalculator.cpp
    FeatureInteractionScoreGridCalculator.cpp
    GRAILDataSetGenerator.cpp
    GRAILDescriptorCalculatorImpl.cpp
    GRAILDescriptorCalculator.cpp
    GRAILXDescriptorCalculator.cpp
    BindingAffinityCalculator.cpp
    
    CDFAttributedGridPropertyReader.cpp
    CDFAttributedGridPropertyWriter.cpp

    AttributedGridPropertyFunctions.cpp
    MoleculeFunctions.cpp
    FeatureExtendedTypeFunction.cpp
    )
  
if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-grail-static STATIC ${cdpl-grail_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  set_target_properties(cdpl-grail-static PROPERTIES 
    OUTPUT_NAME cdpl-grail
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_GRAIL_STATIC_LINK")

  target_link_libraries(cdpl-grail-static cdpl-chem-static cdpl-pharm-static cdpl-molprop-static cdpl-grid-static
    cdpl-biomol-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-forcefield-static)

  install(TARGETS cdpl-grail-static DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)
    
add_library(cdpl-grail-shared SHARED ${cdpl-grail_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

target_link_libraries(cdpl-grail-shared cdpl-chem-shared cdpl-pharm-shared cdpl-molprop-shared cdpl-grid-shared
  cdpl-biomol-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-forcefield-shared)

set_target_properties(cdpl-grail-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-grail
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-grail.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-grail.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-grail.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
  @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-grail-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-grail-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)
