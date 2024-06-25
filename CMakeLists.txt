        
        
# 指定所需的最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 定义项目的名称和使用的语言
project(mrpcFramework LANGUAGES CXX)

# 设置变量的值
set(CMAKE_CXX_STANDARD 17)

#设置可执行文件输出路径
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#设置库文件输出路径
# set(LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/lib)

# 设置头文件搜索路径
# include_directories(${PROJECT_SOURCE_DIR}/src/include)
# include_directories(${PROJECT_SOURCE_DIR}/example)


# add_subdirectory(src)
add_subdirectory(example)
