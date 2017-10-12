INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-grid_LIB_SRCS
    AttributedGridProperty.cpp
    AttributedGridPropertyDefault.cpp

    ControlParameter.cpp
    ControlParameterDefault.cpp
    DataFormat.cpp  

    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFDRegularGridReader.cpp
    CDFDRegularGridWriter.cpp
    CDFDRegularGridSetReader.cpp
    CDFDRegularGridSetWriter.cpp
    CDFRegularGridDataReader.cpp
    CDFRegularGridDataWriter.cpp
    CDFRegularGridSetDataReader.cpp
    CDFRegularGridSetDataWriter.cpp

    AttributedGridPropertyFunctions.cpp
    ControlParameterFunctions.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

IF(Boost_ATOMIC_FOUND)
  LINK_LIBRARIES(${Boost_ATOMIC_LIBRARY})
ENDIF(Boost_ATOMIC_FOUND)

ADD_LIBRARY(cdpl-grid-static STATIC ${cdpl-grid_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-grid-static cdpl-base-static cdpl-util-static cdpl-internal-static)

SET_TARGET_PROPERTIES(cdpl-grid-static PROPERTIES 
                      OUTPUT_NAME cdpl-grid
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_GRID_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

INSTALL(TARGETS cdpl-grid-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-grid-shared SHARED ${cdpl-grid_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-grid-shared cdpl-base-shared  cdpl-util-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-grid-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Grid
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-grid-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-grid
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-grid.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-grid-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
