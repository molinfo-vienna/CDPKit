INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(xlogp-reg_SRCS XLogPReg.cpp)

ADD_EXECUTABLE(xlogp-reg ${xlogp-reg_SRCS})

TARGET_LINK_LIBRARIES(xlogp-reg cdpl-chem-shared)


SET(logs-reg_SRCS LogSReg.cpp)

ADD_EXECUTABLE(logs-reg ${logs-reg_SRCS})

TARGET_LINK_LIBRARIES(logs-reg cdpl-chem-shared)

