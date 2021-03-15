set(BINARY math_parser)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

set(CMAKE_CXX_FLAGS_PROF
  "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pg -no-pie -fno-builtin"
   CACHE STRING "Flags used for cprof profiler build."
   FORCE)

set(SRC ../src/)

####################################
# main executable
####################################

file(GLOB SOURCE_FILES ${SRC}/*cc ${SRC}/*h)

# Adding the executable
add_executable(${BINARY} ${SOURCE_FILES})

target_include_directories(${BINARY} PUBLIC ${SRC})

# Adding the library
add_library(parser SHARED ${SOURCE_FILES})

target_include_directories(parser PUBLIC ${SRC})

