cmake_minimum_required(VERSION 3.10)
project(GameCore)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 关键：添加项目根目录为头文件搜索路径，确保跨文件夹引用
include_directories(${PROJECT_SOURCE_DIR})

# 收集所有源文件（cardsystem 和 RoleSystem）
file(GLOB CARD_SOURCES "cardsystem/*.cpp")
file(GLOB ROLE_SOURCES "RoleSystem/*.cpp")

# 生成可执行文件
add_executable(GameMain main.cpp ${CARD_SOURCES} ${ROLE_SOURCES})

# 编译选项（可选，增强代码规范性）
if(MSVC)
    target_compile_options(GameMain PRIVATE /W4)
else()
    target_compile_options(GameMain PRIVATE -Wall -Wextra)
endif()