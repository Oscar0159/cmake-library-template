cmake_minimum_required(VERSION 3.15)

project(
    ${CMAKE_PROJECT_NAME}_test
    LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

foreach(test_file ${${CMAKE_PROJECT_NAME}_TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} ${CMAKE_PROJECT_NAME} GTest::gtest_main)

    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin
    )

    if (${CMAKE_PROJECT_NAME}_BUILD_SHARED_LIBS)
        add_custom_command(
            TARGET ${test_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
                $<TARGET_FILE_DIR:${test_name}>
        )
    endif()
    
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
