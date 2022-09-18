cmake_minimum_required (VERSION 3.10)

project(CppDesignPattern CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找对应目录下所有源文件
#CMAKE_CURRENT_SOURCE_DIR 为cmakelist当前路径
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src Src_Dir)

#生成可执行文件，同工程名
add_executable(${PROJECT_NAME} ${Src_Dir})

#生成目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#启动项
if (MSVC)
	if (NOT ${CMAKE_VERSION} VERSION_LESS "3.6.0")
		  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	endif ()
endif (MSVC)
