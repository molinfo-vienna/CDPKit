INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(cdpl-util_LIB_SRCS
    SHA1.cpp
   )

ADD_LIBRARY(cdpl-util-static STATIC ${cdpl-util_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-util-static cdpl-base-static)

SET_TARGET_PROPERTIES(cdpl-util-static PROPERTIES 
                      OUTPUT_NAME cdpl-util
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

INSTALL(TARGETS cdpl-util-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-util-shared SHARED ${cdpl-util_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-util-shared cdpl-base-shared)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-util-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Util
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-util-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-util
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-util.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-util-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
