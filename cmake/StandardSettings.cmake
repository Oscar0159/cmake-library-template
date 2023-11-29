#
# 專案設定
#
option(${PROJECT_NAME}_BUILD_SHARED_LIBS "Build ${PROJECT_NAME} as a shared library" ON)
option(${PROJECT_NAME}_BUILD_HEADERS_ONLY "Build only the headers of ${PROJECT_NAME}" OFF)
option(${PROJECT_NAME}_BUILD_EXAMPLES "Build the examples of ${PROJECT_NAME}" OFF)
option(${PROJECT_NAME}_BUILD_TESTS "Build the tests of ${PROJECT_NAME}" ON)

#
# 編譯器設定
#
option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)