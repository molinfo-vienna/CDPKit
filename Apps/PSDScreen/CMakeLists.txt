INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${APPS_SOURCE_DIR}")

SET(psd-screen_SRCS
    Main.cpp
    PSDScreenImpl.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

ADD_EXECUTABLE(psd-screen ${psd-screen_SRCS})

SET_TARGET_PROPERTIES(psd-screen PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/psd-screen")
CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
               @ONLY
              )

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")

TARGET_LINK_LIBRARIES(psd-screen app-utils-static cdpl-util-shared cdpl-base-shared cdpl-chem-shared 
		      cdpl-pharm-shared cdpl-biomol-shared)

INSTALL(TARGETS psd-screen DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
