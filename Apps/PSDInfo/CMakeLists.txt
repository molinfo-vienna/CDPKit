INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${APPS_SOURCE_DIR}")

SET(psd-info_SRCS
    Main.cpp
    PSDInfoImpl.cpp
   )

ADD_EXECUTABLE(psd-info ${psd-info_SRCS})

SET_TARGET_PROPERTIES(psd-info PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/psd-info")
CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
               @ONLY
              )

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")

TARGET_LINK_LIBRARIES(psd-info app-utils-static cdpl-pharm-shared cdpl-util-shared)

INSTALL(TARGETS psd-info DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
