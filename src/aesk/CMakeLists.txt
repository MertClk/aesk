cmake_minimum_required(VERSION 2.8.3)
project(aesk)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g3 -O3")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -g3 -O3")


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_BUILD_TYPE RELEASE)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)

find_package(catkin REQUIRED COMPONENTS
        geometry_msgs
        nav_msgs
        sensor_msgs
        roscpp
        rospy
        std_msgs
        dynamic_reconfigure
        tf
        tf_conversions
        image_transport
        cv_bridge
        OpenCV
        )




catkin_package(
        CATKIN_DEPENDS
        geometry_msgs
        nav_msgs
        roscpp
        rospy
        std_msgs
        DEPENDS
        EIGEN3
        OpenCV
)


include_directories(
        ${Boost_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${catkin_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        ${PCL_INCLUDE_DIRS}
        /usr/local/include
)

link_directories(
        ${CMAKE_BINARY_DIR}/bin
        /usr/local/lib

)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(aesk
        src/main.cpp)

target_link_libraries(aesk
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        ${catkin_LIBRARIES}
        ${PCL_LIBRARIES}
        )

add_dependencies(aesk ${catkin_EXPORTED_TARGETS})
