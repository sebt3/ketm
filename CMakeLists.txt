cmake_minimum_required (VERSION 2.8.7)
project (ketm)
include(GNUInstallDirs)

####
## Compiler option
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
#set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} ")

####
## Dependencies
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(PkgConfig REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_gfx REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)
include_directories(SYSTEM ${SDLGFX_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} ${SDL_INCLUDE_DIR})

####
## Sources
#
file (GLOB	HEADER_FILES "include/*.h")
file (GLOB	SOURCE_FILES "src/*.c")

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

####
## Targets
#

add_executable(ketm ${SOURCE_FILES})
target_link_libraries(ketm m ${SDLGFX_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARIES} ${SDL_LIBRARY})
install(TARGETS ketm DESTINATION bin COMPONENT binaries)


####
## Usefull debug stuff
#
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

