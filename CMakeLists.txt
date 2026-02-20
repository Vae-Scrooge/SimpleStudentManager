# ========================================
# CMakeLists.txt - 项目构建配置文件
# ========================================
#
# CMake 是一个跨平台的构建工具，可以生成各种编译器的项目文件。
# 这个文件告诉 CMake 如何编译我们的项目。
#
# 大一学生只需要理解几个核心概念：
# 1. cmake_minimum_required - 要求的 CMake 最低版本
# 2. project - 定义项目名称和使用的语言
# 3. add_library - 创建库文件（可以复用的代码）
# 4. target_include_directories - 告诉编译器头文件在哪里
# ========================================

cmake_minimum_required(VERSION 3.14...3.22)

# ---- 项目定义 ----
# 项目名称：SimpleStudentManager（简单学生管理系统）
# 版本：1.0
# 语言：CXX（即 C++）
project(
  SimpleStudentManager
  VERSION 1.0
  LANGUAGES CXX
)

# ---- 防止在源代码目录内构建 ----
# 这行代码防止用户在源代码目录中运行 cmake，
# 避免生成的临时文件污染源代码。
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
    "请不要在源代码目录中构建项目！"
    "请创建一个单独的 build 目录，然后在那里运行 cmake。"
  )
endif()

# ---- 使用 CPM 添加依赖 ----
# CPM.cmake 是一个现代的 C++ 包管理器
# 参见 https://github.com/cpm-cmake/CPM.cmake 了解更多
include(cmake/CPM.cmake)

# PackageProject.cmake 用于创建可安装的目标
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# ---- 查找所有源文件 ----
# GLOB_RECURSE 会递归查找所有匹配的文件
# CONFIGURE_DEPENDS 让 CMake 在文件变化时自动更新文件列表
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- 创建库 ----
# STATIC 表示静态库（编译时链接到程序中）
# 也可以用 SHARED 创建动态库（运行时加载）
add_library(${PROJECT_NAME} ${headers} ${sources})

# ---- 设置 C++ 标准 ----
# 使用 C++17 标准（2017年发布的 C++ 版本）
# 这是目前广泛使用的稳定版本，大一学生学的基础语法都支持
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# ---- MSVC 编译器特殊设置 ----
# 强制使用标准一致的编译模式
target_compile_options(
  ${PROJECT_NAME}
  PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
)

# ---- 设置头文件包含路径 ----
# PUBLIC 表示这个路径对使用这个库的其他代码也可见
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- 创建可安装的目标 ----
# 这允许其他项目通过 find_package 使用我们的库
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
)
