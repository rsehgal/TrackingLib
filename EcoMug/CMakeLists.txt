#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(B1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)
#file(GLOB sources ${CMAKE_SOURCE_DIR}/src/*.cc ${CMAKE_SOURCE_DIR}/src/*.cpp)
#file(GLOB headers ${CMAKE_SOURCE_DIR}/include/*.hh ${CMAKE_SOURCE_DIR}/include/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

find_package(ROOT REQUIRED)
#message(STATUS "ROOT LIB : ${ROOT_LIBRARIES}")
#message(STATUS "ROOT  INC: ${ROOT_INCLUDE_DIRS}")
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(inc)
#include_directories(.)
add_executable(test test/test.cpp)
target_link_libraries(test ${ROOT_LIBRARIES})
#target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ABData ${TrackingLib_LIBRARIES})
#add_executable(testSingletonEcoMug testSingletonEcoMug.cpp)
#target_link_libraries(testSingletonEcoMug ${ROOT_LIBRARIES})
add_executable(testSingleTon_T test/testSingleTon_T.cpp )#SingleTon_T.cpp)
target_link_libraries(testSingleTon_T ${ROOT_LIBRARIES})


