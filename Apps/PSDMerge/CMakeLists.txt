INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${APPS_SOURCE_DIR}")

SET(psd-merge_SRCS
    Main.cpp
    PSDMergeImpl.cpp
   )

LINK_LIBRARIES(${Boost_CHRONO_LIBRARY})

ADD_EXECUTABLE(psd-merge ${psd-merge_SRCS})

SET_TARGET_PROPERTIES(psd-merge PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/psd-merge")
CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
               @ONLY
              )

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")

TARGET_LINK_LIBRARIES(psd-merge app-utils-static cdpl-pharm-shared cdpl-util-shared)

INSTALL(TARGETS psd-merge DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
