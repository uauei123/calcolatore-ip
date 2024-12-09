cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(FLTK REQUIRED)

add_executable(app
    src/main.cpp
    src/ip.cpp
    src/subnet.cpp
    src/util.cpp
    fluid/ui.cxx
)

target_link_libraries(app PUBLIC ${FLTK_LIBRARIES})

if(WIN32)
    if(MINGW)
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
        endif()
        target_link_libraries(app PUBLIC gdiplus)
    else()
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            set_target_properties(app PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
        endif()
        target_link_libraries(app PUBLIC gdiplus)
    endif()
elseif(UNIX)
    target_link_libraries(app PUBLIC X11)
endif()


target_include_directories(app PUBLIC ${FLTK_INCLUDE_DIR})
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/fluid)
