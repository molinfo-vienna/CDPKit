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

if(NUMPY_FOUND)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${NUMPY_INCLUDE_DIRS}")
else(NUMPY_FOUND)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
endif(NUMPY_FOUND)

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
endforeach(PYTHON_FILE)

set(grid_MOD_SRCS
    Module.cpp
    AttributedGridExport.cpp
    SpatialGridExport.cpp
    RegularGridExport.cpp
    RegularGridSetExport.cpp

    AttributedGridPropertyExport.cpp 
    AttributedGridPropertyDefaultExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 
    DataFormatExport.cpp 

    RegularGridInputHandlerExport.cpp
    RegularGridOutputHandlerExport.cpp
    RegularGridSetInputHandlerExport.cpp
    RegularGridSetOutputHandlerExport.cpp

    RegularGridIOManagerExport.cpp
    RegularGridSetIOManagerExport.cpp

    RegularGridReaderExport.cpp
    RegularGridWriterExport.cpp
    RegularGridSetReaderExport.cpp
    RegularGridSetWriterExport.cpp

    CDFRegularGridInputHandlerExport.cpp
    CDFRegularGridOutputHandlerExport.cpp
    CDFRegularGridSetInputHandlerExport.cpp
    CDFRegularGridSetOutputHandlerExport.cpp

    CDFRegularGridReaderExport.cpp
    CDFRegularGridWriterExport.cpp
    CDFRegularGridSetReaderExport.cpp
    CDFRegularGridSetWriterExport.cpp

    AttributedGridFunctionExport.cpp 
    ControlParameterFunctionExport.cpp 

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

if(NUMPY_FOUND)
  set(grid_MOD_SRCS
      ${grid_MOD_SRCS}
      ../Math/NumPy.cpp
     )
endif(NUMPY_FOUND)

add_library(_grid MODULE ${grid_MOD_SRCS})

target_link_libraries(_grid cdpl-grid-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_grid PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_grid PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Grid/_grid.pyd")
else(WIN32)
  set_target_properties(_grid PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Grid/_grid.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Grid" COMPONENT CDPLPythonModules)
install(TARGETS _grid DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Grid" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
