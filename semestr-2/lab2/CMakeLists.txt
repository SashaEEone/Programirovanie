cmake_minimum_required(VERSION 3.10)
project(labCMake C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
option(BUILD_SHARED_LIBS "Создать динамическую библиотеку?" OFF)
add_executable(main src/main.c)
add_library(student_lib src/student.c)
target_link_libraries(main student_lib) 
add_custom_target(run
    COMMAND ./main
    DEPENDS main
    COMMENT "Запуск ./main"
)