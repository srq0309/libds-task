﻿cmake_minimum_required(VERSION 3.4)

project(libds-task)

include(${PROJECT_SOURCE_DIR}/script/custom_binary.cmake)
if(WIN32)
    include(${PROJECT_SOURCE_DIR}/script/custom_msvc.cmake)    
endif(WIN32)

include_directories(${PROJECT_SOURCE_DIR}/include)

# 本项目仅需要包含头文件，以下是测试程序

# 工具杂项
add_subdirectory(${PROJECT_SOURCE_DIR}/src/utils)

# 线程安全数据结构
add_subdirectory(${PROJECT_SOURCE_DIR}/src/threadsafe)