target_sources(${PROJECT_NAME}
PRIVATE
full_box.cpp
enemy.cpp
mario.cpp
money.cpp
jumping_enemy.cpp
flying_enemy.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)