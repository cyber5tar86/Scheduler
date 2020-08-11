cmake_minimum_required(VERSION 3.7)
project(BosmaScheduler)


# Option.
set(BosmaScheduler_BuildTests "build tests" ON)

# 3rdparty
if(NOT TARGET ccronexpr_static)
  add_subdirectory(3rdparty/ccronexpr)
endif()
if(NOT TARGET CTPL)
  add_subdirectory(3rdparty/CTPL)
endif()


# packages
find_package(Threads REQUIRED)

# Target.
add_library(Scheduler INTERFACE)
target_include_directories(Scheduler INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(Scheduler INTERFACE
  ccronexpr_static
  Threads::Threads
  CTPL
)  

# tests.
if(BosmaScheduler_BuildTests)
  add_subdirectory(tests)
endif()

