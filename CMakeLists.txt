cmake_minimum_required(VERSION 3.10)
project(GameCore)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加项目根目录为头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR})

# 收集所有源文件（包含Difficulty模块、cardsystem和RoleSystem）
file(GLOB CARD_SOURCES "cardsystem/*.cpp")
file(GLOB ROLE_SOURCES "RoleSystem/*.cpp")
file(GLOB DIFFICULTY_SOURCES "Difficulty.cpp")  # 添加Difficulty源文件

# 生成可执行文件，包含所有模块源文件
add_executable(GameMain 
    main.cpp 
    ${CARD_SOURCES} 
    ${ROLE_SOURCES} 
    ${DIFFICULTY_SOURCES}  # 引入Difficulty模块
)

# 编译选项
if(MSVC)
    target_compile_options(GameMain PRIVATE /W4)
else()
    target_compile_options(GameMain PRIVATE -Wall -Wextra)
endif()