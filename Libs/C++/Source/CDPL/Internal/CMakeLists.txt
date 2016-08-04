INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

IF(CMAKE_COMPILER_IS_GNUCC AND UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF(CMAKE_COMPILER_IS_GNUCC AND UNIX)

SET(cdpl-internal_LIB_SRCS
    StringUtilities.cpp
    StringDataIOUtilities.cpp
    SHA1.cpp
   )

ADD_LIBRARY(cdpl-internal-static STATIC ${cdpl-internal_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-internal-static PROPERTIES 
                      OUTPUT_NAME cdpl-internal
                      CLEAN_DIRECT_OUTPUT 1
                     )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
