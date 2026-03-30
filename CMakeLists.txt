cmake_minimum_required(VERSION 3.10)

project(Graph VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main[.]cpp$")

add_library(${PROJECT_NAME}_lib STATIC ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME}_lib PUBLIC ${INCLUDE_DIR})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(${PROJECT_NAME} "src/main.cpp")

    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

else()
    message(WARNING "main.cpp not found in src/ directory")
endif()

enable_testing()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

    if(TEST_SOURCES)
        add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

        target_include_directories(${PROJECT_NAME}_tests PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/external
        )


        target_link_libraries(${PROJECT_NAME}_tests PRIVATE
                ${PROJECT_NAME}_lib
        )

        add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_tests)
    endif()
endif()