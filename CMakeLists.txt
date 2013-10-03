# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
# This should be 2.8.0 to have FindGTK2 module
IF (COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 OLD)
  CMAKE_POLICY(SET CMP0005 OLD)
  CMAKE_POLICY(SET CMP0011 OLD)
ENDIF (COMMAND cmake_policy)

PROJECT(remembrancer_pi)

SET(PACKAGE_NAME remembrancer_pi)
SET(PLUGIN_SOURCE_DIR ..)
MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")

#SET(CMAKE_BUILD_TYPE Debug)

IF (PREFIX)
	SET(CMAKE_INSTALL_PREFIX ${PREFIX})
ENDIF (PREFIX)

SET(PARENT opencpn)
SET(PREFIX_BIN bin)
SET(PREFIX_INCLUDE include)
SET(PREFIX_DATA share)
SET(PREFIX_PARENTDATA ${PREFIX_DATA}/${PARENT})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# require proper c++
#ADD_DEFINITIONS( "-Wall -ansi -pedantic -Wno-variadic-macros" )
#TODO: Should we use  -fno-stack-protector
#  IF NOT DEBUGGING CFLAGS="-O2 -march=native"
IF(NOT WIN32)
 ADD_DEFINITIONS( "-Wall -g -fexceptions -fvisibility=hidden" )

 IF(NOT APPLE)
  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,-Bsymbolic")
 ELSE(NOT APPLE)
  SET(CMAKE_SHARED_LINKER_FLAGS "-Wl")
 ENDIF(NOT APPLE)

ENDIF(NOT WIN32)

# Add some definitions to satisfy MS
IF(WIN32)
    ADD_DEFINITIONS(-D__MSVC__)
    ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE)
ENDIF(WIN32)


SET(wxWidgets_USE_LIBS base core net xml html adv)
SET(BUILD_SHARED_LIBS TRUE)
FIND_PACKAGE(wxWidgets REQUIRED)

INCLUDE(${wxWidgets_USE_FILE})

FIND_PACKAGE(Gettext REQUIRED)

# For convenience we define the sources as a variable. You can add
# header files and cpp/c files and CMake will sort them out


SET(SRC_REMEMBRANCER
    src/remembrancer_pi.cpp
    src/remembrancer_pi.h
    src/dialogDefinitions.cpp
    src/dialogDefinitions.h
    src/icons.cpp
    src/icons.h
 	)

SET(SRC_NMEA0183
		include/nmea0183/LatLong.hpp
		include/nmea0183/latlong.cpp
		include/nmea0183/long.cpp
		include/nmea0183/nmea0183.cpp
		include/nmea0183/nmea0183.hpp
		include/nmea0183/Response.hpp
		include/nmea0183/response.cpp
		include/nmea0183/RMB.hpp
		include/nmea0183/rmb.cpp
		include/nmea0183/Sentence.hpp
		include/nmea0183/sentence.cpp
		include/nmea0183/talkerid.cpp
		include/nmea0183/RMC.HPP
		include/nmea0183/rmc.cpp
		include/nmea0183/hexvalue.cpp
		include/nmea0183/lat.cpp
		include/nmea0183/expid.cpp
		include/nmea0183/wpl.hpp
		include/nmea0183/wpl.cpp
		include/nmea0183/rte.hpp
		include/nmea0183/rte.cpp
		include/nmea0183/hdt.hpp
		include/nmea0183/hdt.cpp
		include/nmea0183/hdg.hpp
		include/nmea0183/hdg.cpp
		include/nmea0183/hdm.hpp
		include/nmea0183/hdm.cpp
		include/nmea0183/gll.hpp
		include/nmea0183/gll.cpp
		include/nmea0183/vtg.hpp
		include/nmea0183/vtg.cpp
		include/nmea0183/gga.hpp
		include/nmea0183/gga.cpp
		include/nmea0183/gsv.hpp
		include/nmea0183/gsv.cpp
	)
INCLUDE_DIRECTORIES(nmea0183 opencpn)

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_REMEMBRANCER} ${SRC_NMEA0183} )

IF(WIN32)
  SET(OPENCPN_IMPORT_LIB "../../../${CMAKE_CFG_INTDIR}/${PARENT}")
  TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${OPENCPN_IMPORT_LIB} )
  ADD_DEPENDENCIES(${PACKAGE_NAME} ${PARENT})
ENDIF(WIN32)

TARGET_LINK_LIBRARIES( ${PACKAGE_NAME} ${wxWidgets_LIBRARIES} )

IF(UNIX)
INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME LIBRARY DESTINATION ${PREFIX_PARENTDATA}/plugins)
ENDIF(UNIX)

IF(WIN32)
INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME DESTINATION "plugins")
ENDIF(WIN32)

