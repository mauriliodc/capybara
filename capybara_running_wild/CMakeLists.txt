cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)

rosbuild_init()
add_definitions( -D_LINUX_ )
#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/rodent.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
rosbuild_add_executable(
	roditore 
	src/capybara.h src/capybara.cpp
	src/serialFriend.h src/serialFriend.cpp
	src/packets.cpp src/packets.h
	src/platform_defs.cpp src/platform_defs.h
	src/querycommands_packet.cpp src/querycommands_packet.h
	src/packet_handler.cpp src/packet_handler.h 
	src/hexmessage.cpp src/hexmessage.h
	src/state_packet.cpp src/state_packet.h
	src/speed_packet.cpp src/speed_packet.h
	src/pid_packet.cpp src/pid_packet.h
	src/odometrycalib_packet.cpp src/odometrycalib_packet.h
	src/wheelSpeed_packet.cpp src/wheelSpeed_packet.h
	src/rodent.cpp 
	)
#target_link_libraries(example ${PROJECT_NAME})
