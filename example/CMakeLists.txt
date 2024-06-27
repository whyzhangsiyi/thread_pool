set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


set(CMAKE_BUILD_TYPE Debug)
#设置库文件输出路径
set(LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/lib)


# 设置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/example)
aux_source_directory( ${PROJECT_SOURCE_DIR}/src/include Thread_code)
add_executable(example main_test.cpp ${Thread_code})
