cmake_minimum_required(VERSION 3.21)
project(AdventOfCode2021)

set(CMAKE_CXX_STANDARD 17)

function(create day)
    add_executable(${day} ${day}/main.cpp)
    add_custom_command(
        TARGET ${day} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/${day}/${day}.txt
        ${CMAKE_CURRENT_BINARY_DIR}/${day}.txt
    )
    if (EXISTS ${CMAKE_SOURCE_DIR}/${day}/${day}-mock.txt)
        add_custom_command(
            TARGET ${day} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/${day}/${day}-mock.txt
            ${CMAKE_CURRENT_BINARY_DIR}/${day}-mock.txt
        )
    endif ()
endfunction()

create(day1)
create(day2)
create(day3)
create(day4)
