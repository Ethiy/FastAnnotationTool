cmake_minimum_required(VERSION 3.2)
include(CheckCXXCompilerFlag)
project(FIAT CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CHECK_CXX_COMPILER_USED1)
# Using Visual Studio C++
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "MSVCx")
# Using Intel C++
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "Intelx")
else(CHECK_CXX_COMPILER_USED1)
    # GCC or Clang
    # At least C++11
    CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
    CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    elseif(COMPILER_SUPPORTS_CXX1Z)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
    elseif(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif(COMPILER_SUPPORTS_CXX1Y)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    elseif(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else(COMPILER_SUPPORTS_CXX17)
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif(COMPILER_SUPPORTS_CXX17)

    if(CHECK_CXX_COMPILER_USED2)
    elseif("${CMAKE_CXX_COMPILER_ID}x" MATCHES "Clangx")
        # Using Clang
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors")
    elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "GNUx")
        # Using GCC
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    endif(CHECK_CXX_COMPILER_USED2)
endif(CHECK_CXX_COMPILER_USED1)

#OpenCV
FIND_PACKAGE(OpenCV REQUIRED core imgproc highgui imgcodecs)
if(OpenCV_Found)
    INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})
endif(OpenCV_Found)

#Boost
FIND_PACKAGE(Boost REQUIRED program_options filesystem)
if(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
else(Boost_FOUND)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/local/boost_1_60_0/")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/local/boost_1_60_0/lib64-msvc-14.0")
    Find_PACKAGE(Boost)
    if(Boost_FOUND)
        INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    endif(Boost_FOUND)
endif(Boost_FOUND)

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           OFF)

# Annotation Lib
file(GLOB_RECURSE FIAT_LIB_HEADERS
	"${FIAT_SOURCE_DIR}/src/image/*.h" "${FIAT_SOURCE_DIR}/src/annotation/*.h" "${FIAT_SOURCE_DIR}/src/tools/*.h"
)

file(GLOB_RECURSE FIAT_LIB_SRC
	"${FIAT_SOURCE_DIR}/src/image/Image.cpp" "${FIAT_SOURCE_DIR}/src/annotation/*.cpp" "${FIAT_SOURCE_DIR}/src/tools/*.cpp"
)

add_library(utilities ${INCLUDE_DIRECTORIES} ${FIAT_LIB_HEADERS} ${FIAT_LIB_SRC})
target_link_libraries (utilities ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} )

if(CHECK_CXX_COMPILER_USED_UTILITIES)

elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "MSVCx")
  # using Visual Studio C++
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "Intelx")
  # using Intel C++
else()
  # GCC or Clang
	target_link_libraries (utilities m )
endif(CHECK_CXX_COMPILER_USED_UTILITIES)

# Annotate
file(GLOB_RECURSE FIAT_ANNOTATE_HEADERS
)

file(GLOB_RECURSE FIAT_ANNOTATE_SRC
	"${FIAT_SOURCE_DIR}/src/run/annotate.cpp"
)

add_executable(annotate ${INCLUDE_DIRECTORIES} ${FIAT_LIB_HEADERS} ${FIAT_ANNOTATE_HEADERS} ${FIAT_ANNOTATE_SRC})
target_link_libraries(annotate utilities ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})


if(CHECK_CXX_COMPILER_USED_ANNOTATE)
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "MSVCx")
  # using Visual Studio C++
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "Intelx")
  # using Intel C++
else()
  # GCC or Clang
	target_link_libraries (annotate m)
endif(CHECK_CXX_COMPILER_USED_ANNOTATE)
