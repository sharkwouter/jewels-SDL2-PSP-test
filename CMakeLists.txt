cmake_minimum_required(VERSION 3.10)

project(jewels)

add_executable(${PROJECT_NAME} main.c)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
)

IF(PLATFORM_PSP)
    file(COPY platform/psp/ICON0.PNG DESTINATION ${CMAKE_BINARY_DIR})

    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH ICON0.PNG
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
    )
ELSEIF(VITA)
    set(VITA_TITLEID "JWLT00001")

    include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

    vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
    vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
        VERSION "01.00"
        NAME ${PROJECT_NAME}
        FILE platform/vita/sce_sys sce_sys
        FILE block.bmp block.bmp
    )
ENDIF()

if(NOT DEFINED VITA)
        file(COPY block.bmp DESTINATION ${CMAKE_BINARY_DIR})
endif()
