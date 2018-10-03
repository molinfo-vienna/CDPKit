INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SystemInfo.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/SystemInfo.hpp")

SET(app-utils_LIB_SRCS
    CmdLineBase.cpp
    HelperFunctions.cpp
   )

LINK_LIBRARIES(${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_CHRONO_LIBRARY} ${Boost_ATOMIC_LIBRARY})

ADD_LIBRARY(app-utils-static STATIC ${app-utils_LIB_SRCS})

SET_TARGET_PROPERTIES(app-utils-static PROPERTIES 
                      OUTPUT_NAME app-utils
                      CLEAN_DIRECT_OUTPUT 1
                     )

TARGET_LINK_LIBRARIES(app-utils-static cdpl-util-shared cdpl-base-shared)
