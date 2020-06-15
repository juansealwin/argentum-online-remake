cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I msgpack-c/include.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)
set(PROTOCOL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../protocol)
set(NET_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../net)
set(UTIL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../util)

find_package(SDL2 REQUIRED)
find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
find_package(Threads)

INCLUDE(FindPkgConfig) 
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
#PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
#PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${PROTOCOL_SOURCE_DIR})
include_directories(${NET_SOURCE_DIR})
include_directories(${UTIL_SOURCE_DIR})


#qt5_wrap_ui(UIS_HEADERS
#	${PROJECT_SOURCE_DIR}/qtdesigner/clientlobby.ui
#)

#SET(UI_RESOURCES
#	${PROJECT_SOURCE_DIR}/qtdesigner/client_lobby_resources.qrc
#)

#QT5_ADD_RESOURCES(UI_RESOURCES_RCC ${UI_RESOURCES})

file(GLOB client_source_files *.cpp)
file(GLOB client_header_files *.h)

file(GLOB common_source_files ${COMMON_SOURCE_DIR}/*.cpp)
file(GLOB common_header_files ${COMMON_SOURCE_DIR}/*.h)

file(GLOB protocol_source_files ${PROTOCOL_SOURCE_DIR}/*.cpp)
file(GLOB protocol_header_files ${PROTOCOL_SOURCE_DIR}/*.h)

file(GLOB net_source_files ${NET_SOURCE_DIR}/*.cpp)
file(GLOB net_header_files ${NET_SOURCE_DIR}/*.h)

file(GLOB util_source_files ${UTIL_SOURCE_DIR}/*.cpp)
file(GLOB util_header_files ${UTIL_SOURCE_DIR}/*.h)

add_executable(client
		${client_source_files}
		${client_header_files}
		${common_source_files}
		${common_header_files}
		${protocol_source_files}
		${protocol_header_files}
		${net_source_files}
		${net_header_files}
    ${util_source_files}
		${util_header_files}
		)

#target_link_libraries(client Qt5::Widgets Qt5::DBus)
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

#Install the images
install(DIRECTORY assets/ DESTINATION ${CMAKE_BINARY_DIR}/client)

