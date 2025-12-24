cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(HEADERS
    qt_game/qt_game_window.hpp
    qt_game/qt_ui_factory.hpp
    qt_game/qt_ui_obj_rect_adapter.hpp
    qt_game/ui_objects/qt_box.hpp
    qt_game/ui_objects/qt_enemy.hpp
    qt_game/ui_objects/qt_flying_enemy.hpp
    qt_game/ui_objects/qt_full_box.hpp
    qt_game/ui_objects/qt_jumping_enemy.hpp
    qt_game/ui_objects/qt_mario.hpp
    qt_game/ui_objects/qt_money.hpp
    qt_game/ui_objects/qt_ship.hpp
)

set(SOURCES 
    main.cpp
    qt_game/qt_game_window.cpp
    qt_game/qt_ui_factory.cpp
    qt_game/qt_ui_obj_rect_adapter.cpp
    qt_game/ui_objects/qt_box.cpp
    qt_game/ui_objects/qt_enemy.cpp
    qt_game/ui_objects/qt_flying_enemy.cpp
    qt_game/ui_objects/qt_full_box.cpp
    qt_game/ui_objects/qt_jumping_enemy.cpp
    qt_game/ui_objects/qt_mario.cpp
    qt_game/ui_objects/qt_money.cpp
    qt_game/ui_objects/qt_ship.cpp
    
    os_controls/windows/os_control_settings.cpp
    os_controls/windows/user_input.cpp
    
    controller/game.cpp
    
    levels/first_level.cpp
    levels/game_level.cpp
    levels/second_level.cpp
    levels/third_level.cpp
    
    model/collisionable.cpp
    model/game_map.cpp
    model/movable.cpp
    model/rect.cpp
    model/rect_map_movable_adapter.cpp
    
    objects/full_box.cpp
    objects/enemy.cpp
    objects/mario.cpp
    objects/money.cpp
    objects/jumping_enemy.cpp
    objects/flying_enemy.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/qt_game"
    "${CMAKE_CURRENT_SOURCE_DIR}/qt_game/ui_objects"
    "${CMAKE_CURRENT_SOURCE_DIR}/os_controls/os_api"
    "${CMAKE_CURRENT_SOURCE_DIR}/os_controls/windows"
    "${CMAKE_CURRENT_SOURCE_DIR}/controller"
    "${CMAKE_CURRENT_SOURCE_DIR}/levels"
    "${CMAKE_CURRENT_SOURCE_DIR}/model"
    "${CMAKE_CURRENT_SOURCE_DIR}/objects"
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Gui
)