# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    FragmentLibrary.cdf
   )

FOREACH(DATA_FILE ${DATA_FILES})
  ADD_CUSTOM_COMMAND(OUTPUT "${DATA_FILE}.str"
		     COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/FileDataToCString.py" 
  		     "${CDPKIT_BUILTIN_DATA_DIR}/ConfGen/${DATA_FILE}" 
		     "${DATA_FILE}.str"
		     DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/ConfGen/${DATA_FILE}"
		     )
  SET(DATA_FILE_STRINGS "${DATA_FILE_STRINGS}" "${DATA_FILE}.str") 
ENDFOREACH(DATA_FILE)

SET(cdpl-confgen_LIB_SRCS
    ${DATA_FILE_STRINGS}

    DGConstraintGenerator.cpp
    DGConstraintGeneratorSettings.cpp
    DGStructureGenerator.cpp
    DGStructureGeneratorSettings.cpp
    FragmentLibraryEntry.cpp
    FragmentLibrary.cpp
    TorsionLibrary.cpp
    TorsionRule.cpp
    TorsionCategory.cpp
    TorsionRuleMatch.cpp
    TorsionRuleMatcher.cpp
    RMSDConformerSelector.cpp
    TorsionDriver.cpp
    TorsionDriverImpl.cpp
    TorsionDriverSettings.cpp

    CDFFragmentLibraryDataReader.cpp
    CDFFragmentLibraryDataWriter.cpp
    TorsionLibraryDataReader.cpp
    FragmentTreeNode.cpp

    CDFMoleculeDataFunctions.cpp
    UtilityFunctions.cpp
   )

IF(Boost_TIMER_FOUND AND Boost_CHRONO_FOUND)
   SET(cdpl-confgen_LIB_SRCS
       ${cdpl-confgen_LIB_SRCS}
       RandomStructureGenerator.cpp
       RandomStructureGeneratorSettings.cpp
       ConformerGenerator.cpp
       ConformerGeneratorImpl.cpp
       ConformerGeneratorSettings.cpp
       FragmentConformerGenerator.cpp
       FragmentConformerGeneratorSettings.cpp
       FragmentLibraryGenerator.cpp
       FragmentAssembler.cpp
       FragmentAssemblerImpl.cpp
       FragmentAssemblerSettings.cpp
     )	  

   LINK_LIBRARIES(${Boost_TIMER_LIBRARY} ${Boost_CHRONO_LIBRARY})	
ENDIF(Boost_TIMER_FOUND AND Boost_CHRONO_FOUND)

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

IF(Boost_IOSTREAMS_FOUND)
   LINK_LIBRARIES(${Boost_IOSTREAMS_LIBRARY})
ENDIF(Boost_IOSTREAMS_FOUND)

ADD_LIBRARY(cdpl-confgen-static STATIC ${cdpl-confgen_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-confgen-static PROPERTIES 
                      OUTPUT_NAME cdpl-confgen
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_CONFGEN_STATIC_LINK;CDPL_BASE_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_FORCEFIELD_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-confgen-static cdpl-base-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-forcefield-static cdpl-internal-static)

INSTALL(TARGETS cdpl-confgen-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-confgen-shared SHARED ${cdpl-confgen_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-confgen-shared cdpl-base-shared cdpl-chem-shared cdpl-math-shared cdpl-util-shared cdpl-forcefield-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-confgen-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-ConfGen
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-confgen-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-confgen
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-confgen.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-confgen-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
