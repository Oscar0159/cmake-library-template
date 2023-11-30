#
# 專案設定
#
option(${PROJECT_NAME}_BUILD_SHARED_LIBS "Build ${PROJECT_NAME} as a shared library" ON)
option(${PROJECT_NAME}_BUILD_HEADERS_ONLY "Build only the headers of ${PROJECT_NAME}" OFF)
option(${PROJECT_NAME}_BUILD_EXAMPLES "Build the examples of ${PROJECT_NAME}" OFF)
option(${PROJECT_NAME}_BUILD_TESTS "Build the tests of ${PROJECT_NAME}" ON)

option(${PROJECT_NAME}_USE_ALT_NAMES "Use alternative names for the project, such as naming the include directory all lowercase." ON)

#
# 專案測試設定
#
option(${PROJECT_NAME}_USE_GOOGLE_TEST "Use Google Test as the test framework" ON)
option(${PROJECT_NAME}_FETCH_GOOGLE_TEST "Fetch Google Test automatically" ON)

#
# 編譯器設定
#
option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)