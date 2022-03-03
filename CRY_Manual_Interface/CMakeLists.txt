cmake_minimum_required(VERSION 2.8)
project(CRY_Manual)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
include_directories(Cry/inc)
include_directories(inc)

file(GLOB headersCry ${headersCry} Cry/inc/*.h )
file(GLOB sourcesCry ${sourcesCry} Cry/src/*.cc)
add_library(cry SHARED ${sourcesCry})

add_library(cry_manual_interface SHARED src/cry_manual_interface.cpp src/MuonReader.cpp )
target_link_libraries(cry_manual_interface cry ${ROOT_LIBRARIES})

