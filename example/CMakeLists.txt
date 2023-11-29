cmake_minimum_required(VERSION 3.15)

project(
    ${CMAKE_PROJECT_NAME}_example
    LANGUAGES C
)

foreach(example_file ${${CMAKE_PROJECT_NAME}_EXAMPLE_SOURCES})
    get_filename_component(example_name ${example_file} NAME_WE)
    add_executable(${example_name} ${example_file})
    target_link_libraries(${example_name} PRIVATE ${CMAKE_PROJECT_NAME})
    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/example/bin
    )

    if (${CMAKE_PROJECT_NAME}_BUILD_SHARED_LIBS)
        add_custom_command(
            TARGET ${example_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
                $<TARGET_FILE_DIR:${example_name}>
        )
    endif()
endforeach()