# ========================================
# standalone/CMakeLists.txt - 独立程序构建配置
# ========================================
# 
# 这个文件配置独立可执行程序的编译。
# 独立程序是可以直接运行的 .exe 文件。
# ========================================

cmake_minimum_required(VERSION 3.14...3.22)

project(StudentManagerApp LANGUAGES CXX)

# --- Import tools ----

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/tools.cmake)

# ---- Dependencies ----

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CPM.cmake)

CPMAddPackage(NAME SimpleStudentManager SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "student_manager")

target_link_libraries(${PROJECT_NAME} SimpleStudentManager::SimpleStudentManager)
