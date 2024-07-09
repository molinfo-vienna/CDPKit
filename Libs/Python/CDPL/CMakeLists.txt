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

include_directories("${PYTHON_INCLUDE_DIRS}" "${CMAKE_CURRENT_SOURCE_DIR}")

if(NOT WIN32)
   add_compile_definitions(BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY)
else()
   add_compile_definitions(HAVE_SNPRINTF)
endif()

if(MSVC)
  add_compile_definitions("BOOST_PYTHON_NO_LIB")
endif()

add_compile_definitions("BOOST_BIND_GLOBAL_PLACEHOLDERS")

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"  @ONLY)
endforeach(PYTHON_FILE)

file(GLOB INSTALL_PYTHON_FILES "${CMAKE_CURRENT_BINARY_DIR}/*.py")

set(cdpl_MOD_SRCS
    Module.cpp
    VersionInfoExport.cpp
    ConfigInfoExport.cpp
    BuildInfoExport.cpp
   )

add_library(_cdpl MODULE ${cdpl_MOD_SRCS})
target_link_libraries(_cdpl ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_cdpl PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_cdpl PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/_cdpl.pyd")
else(WIN32)
  set_target_properties(_cdpl PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH1}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/_cdpl.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${INSTALL_PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL" COMPONENT CDPLPythonModules)
install(TARGETS _cdpl DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

add_subdirectory(Base) 
add_subdirectory(Math) 
add_subdirectory(Util) 
add_subdirectory(Chem) 
add_subdirectory(Biomol) 
add_subdirectory(Pharm) 
add_subdirectory(ForceField) 
add_subdirectory(ConfGen)
add_subdirectory(Shape) 
add_subdirectory(Grid) 
add_subdirectory(Vis)
add_subdirectory(Descr)
add_subdirectory(MolProp) 
add_subdirectory(GRAIL)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
