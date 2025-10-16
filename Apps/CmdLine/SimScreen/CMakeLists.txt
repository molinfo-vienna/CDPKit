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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${APPS_SOURCE_DIR}")

set(simscreen_SRCS
    Main.cpp
    SimScreenImpl.cpp
    ScreeningProcessor.cpp
    DescriptorCalculator.cpp
    TanimotoSimilarity.cpp
    TverskySimilarity.cpp
    CosineSimilarity.cpp
    DiceSimilarity.cpp
    ManhattanSimilarity.cpp
    ManhattanDistance.cpp
    EuclideanSimilarity.cpp
    EuclideanDistance.cpp
    HammingDistance.cpp
    ECFPCalculator.cpp
    DaylightFPCalculator.cpp
    PubChemFPCalculator.cpp
    MACCSFPCalculator.cpp
   )

add_executable(simscreen ${simscreen_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

set_target_properties(simscreen PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/simscreen.exe")
else()
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/simscreen")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

target_link_libraries(simscreen cmdline-static cdpl-util-shared cdpl-base-shared cdpl-chem-shared cdpl-pharm-shared 
  cdpl-descr-shared Threads::Threads)

install(TARGETS simscreen DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT Applications)
