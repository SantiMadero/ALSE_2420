cmake_minimum_required(VERSION 3.10)

project(sqlitedb_sensores)
add_executable(${PROJECT_NAME}_sensores_db "sensores_db.cpp")
add_executable(${PROJECT_NAME}_delete_db "delete_db.cpp")
target_link_libraries(${PROJECT_NAME}_delete_db sqlite3)
target_link_libraries(${PROJECT_NAME}_sensores_db sqlite3)

