#
# cmake 最小版本要求
# googletest v1.14.0 需要 cmake 3.13 [https://github.com/google/oss-policies-info/blob/main/foundational-cxx-support-matrix.md]
cmake_minimum_required(VERSION 3.15)

#
# 項目名稱
#
project(
    HelloWorld
    VERSION 1.0.0
    DESCRIPTION "The cmake template for c/c++ library"
    LANGUAGES C CXX
)

#
# 設定C/C++標準
# GoogleTest v1.14.0 需要 CMAKE_CXX_STANDARD 14
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# 設定專案選項
#
include(cmake/StandardSettings.cmake)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
if (UNIX)
    add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")    #this will allow to use same _DEBUG macro available in both Linux as well as Windows - MSCV environment. Easy to put Debug specific code.
endif (UNIX)

#
# 設定專案別名
#
if(${PROJECT_NAME}_USE_ALT_NAMES)
  string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
  string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)
else()
  set(PROJECT_NAME_LOWERCASE ${PROJECT_NAME})
  set(PROJECT_NAME_UPPERCASE ${PROJECT_NAME})
endif()

#
# 防止 in-source build
#
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

#
# 設定靜態分析工具
#
# todo: 這裡可以設定 clang-tidy & cppcheck

#
# 設定包管理工具
#
# todo: 這裡可以設定 conan & vcpkg

#
# 產生專案檔案
#
include(cmake/SourcesAndHeaders.cmake)
if(${PROJECT_NAME}_BUILD_HEADERS_ONLY)
    add_library(${PROJECT_NAME} INTERFACE)
elseif(${PROJECT_NAME}_BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
else()
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIR}>)

#
# 設定專案輸出目錄
#
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    DEBUG_POSTFIX "_d"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${${PROJECT_NAME}_INCLUDES}"
)

#
# 設定專案 C/C++ Flags 和 警告
#
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

#
# 產生專案版本標頭檔案
#
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/version.h.in
  include/${PROJECT_NAME_LOWERCASE}/version.h
  @ONLY
)

#
# 產生專案安裝檔案
#
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/version.h.in
    include/${PROJECT_NAME_LOWERCASE}/version.h
    @ONLY
)

#
# 安裝專案
#
include(GNUInstallDirs)

install(
    TARGETS
    ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION include/${PROJECT_NAME_LOWERCASE}
    PUBLIC_HEADER DESTINATION include/${PROJECT_NAME_LOWERCASE}
)

install(
    EXPORT
    ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME_LOWERCASE}
    DESTINATION
    include
)

#
# Quick `ConfigVersion.cmake` creation
#
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install( FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

#
# 產生專案文件
#
# todo: 這裡可以設定 doxygen
# if (${PROJECT_NAME}_BUILD_DOCS)
#     # add_subdirectory(docs)
# endif()

#
# 產生專案範例
#
if (${PROJECT_NAME}_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

#
# 產生單元測試
#
if (${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()