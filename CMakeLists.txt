#This is the CMake file used to build the extensions.
#For more information, see the Readme.txt file.

cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0011 NEW)

project(Widgets)

#Sanity checks
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  message( "CMAKE_BUILD_TYPE is empty, assuming build type is Release" )
	set(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_SUBDIRECTORY(WidgetsCore)
ADD_SUBDIRECTORY(TextBoxObject)