cmake_minimum_required(VERSION 2.8)
project(RoadDetection)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)

# 包含头文件目录
include_directories(${OpenCV_INCLUDE_DIRS} include)

# 添加源文件
add_executable(road_detection src/main.cpp src/road_detection_sobel.cpp)

# 链接 OpenCV 库
target_link_libraries(road_detection ${OpenCV_LIBS})
