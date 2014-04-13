# Project Properties
cmake_minimum_required( VERSION 2.8 )

PROJECT( MasterThesisWojciechowski ) #Project name
SET (APPLICATION_NAME "Project Name")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2014")
SET (APPLICATION_VERSION_MAJOR 1)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 0)
SET (APPLICATION_VERSION_TYPE SNAPSHOT)
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# LibBoost configuration
# 
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     ON)

FIND_PACKAGE (Boost 1.46 COMPONENTS "date_time" "filesystem" "graph" "iostreams" "program_options" "regex" "serialization" "signals" "system" "thread" "wserialization" REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# 
# OpenCV library configuration
# 
FIND_PACKAGE( OpenCV REQUIRED )

#
# Additional Flags
#

# Debug Image Print(comment if not needed)
# If uncommented, input and output images will be printed
# add_definitions(-DDEBUG_IMAGES)

#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# g++ flags
#
set(CMAKE_CXX_FLAGS "-O2 -Wall -pedantic -Werror")

#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# Add Build Targets
#
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

#
# Add Install Targets
#
IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

