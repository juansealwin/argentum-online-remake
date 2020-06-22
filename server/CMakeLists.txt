cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)
set(PROTOCOL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../protocol)
set(NET_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../net)
set(UTIL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../util)
set(MODEL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/model)
set(ENTITIES_SOURCE_DIR ${PROJECT_SOURCE_DIR}/model/entities)
set(ITEMS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/model/items)
set(MAP_SOURCE_DIR ${PROJECT_SOURCE_DIR}/model/map)
set(COMMANDS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/commands)
set(NOTIFICATIONS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/notifications)




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
include_directories(${MODEL_SOURCE_DIR})
include_directories(${ENTITIES_SOURCE_DIR})
include_directories(${ITEMS_SOURCE_DIR})
include_directories(${MAP_SOURCE_DIR})
include_directories(${COMMANDS_SOURCE_DIR})
include_directories(${NOTIFICATIONS_SOURCE_DIR})




#qt5_wrap_ui(UIS_HEADERS
#	${PROJECT_SOURCE_DIR}/qtdesigner/clientlobby.ui
#)

#SET(UI_RESOURCES
#	${PROJECT_SOURCE_DIR}/qtdesigner/client_lobby_resources.qrc
#)

#QT5_ADD_RESOURCES(UI_RESOURCES_RCC ${UI_RESOURCES})

file(GLOB server_source_files *.cpp)
file(GLOB server_header_files *.h)

file(GLOB common_source_files ${COMMON_SOURCE_DIR}/*.cpp)
file(GLOB common_header_files ${COMMON_SOURCE_DIR}/*.h)

file(GLOB protocol_source_files ${PROTOCOL_SOURCE_DIR}/*.cpp)
file(GLOB protocol_header_files ${PROTOCOL_SOURCE_DIR}/*.h)

file(GLOB net_source_files ${NET_SOURCE_DIR}/*.cpp)
file(GLOB net_header_files ${NET_SOURCE_DIR}/*.h)

file(GLOB util_source_files ${UTIL_SOURCE_DIR}/*.cpp)
file(GLOB util_header_files ${UTIL_SOURCE_DIR}/*.h)

file(GLOB model_source_files ${MODEL_SOURCE_DIR}/*.cpp)
file(GLOB model_header_files ${MODEL_SOURCE_DIR}/*.h)

file(GLOB entities_source_files ${ENTITIES_SOURCE_DIR}/*.cpp)
file(GLOB entities_header_files ${ENTITIES_SOURCE_DIR}/*.h)

file(GLOB items_source_files ${ITEMS_SOURCE_DIR}/*.cpp)
file(GLOB items_header_files ${ITEMS_SOURCE_DIR}/*.h)

file(GLOB map_source_files ${MAP_SOURCE_DIR}/*.cpp)
file(GLOB map_header_files ${MAP_SOURCE_DIR}/*.h)

file(GLOB commands_source_files ${COMMANDS_SOURCE_DIR}/*.cpp)
file(GLOB commands_header_files ${COMMANDS_SOURCE_DIR}/*.h)

file(GLOB notifications_source_files ${NOTIFICATIONS_SOURCE_DIR}/*.cpp)
file(GLOB notifications_header_files ${NOTIFICATIONS_SOURCE_DIR}/*.h)

add_executable(server
		${server_source_files}
		${server_header_files}
		${common_source_files}
		${common_header_files}
		${protocol_source_files}
		${protocol_header_files}
		${net_source_files}
		${net_header_files}
		${util_source_files}
		${util_header_files}
		${model_source_files}
		${model_header_files}
		${entities_source_files}
		${entities_header_files}
		${items_source_files}
		${items_header_files}
		${map_source_files}
		${map_header_files}
		${commands_source_files}
		${commands_header_files}
		${notifications_source_files}
		${notifications_header_files}
		)

#target_link_libraries(server Qt5::Widgets Qt5::DBus)
target_link_libraries(server ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

