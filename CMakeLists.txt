cmake_minimum_required (VERSION 3.10)

project(CppDesignPattern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找对应目录下所有源文件
#CMAKE_SOURCE_DIR 顶层CMakeLists.txt所在文件夹
#PROJECT_SOURCE_DIR 最近的包含project()命令的CMakeLists.txt所在文件夹
#CMAKE_CURRENT_SOURCE_DIR 和(./)等效，最近的CMakeLists.txt所在文件夹
aux_source_directory(${CMAKE_SOURCE_DIR}/src Src_Dir)

#生成可执行文件，同工程名
add_executable(${PROJECT_NAME} ${Src_Dir})

#生成目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#启动项
if (MSVC)
	#指定为UTF8编码
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_UNICODE /DUNICODE")
	#VS默认启动项目
	if (NOT ${CMAKE_VERSION} VERSION_LESS "3.6.0")
		  set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	endif ()
endif (MSVC)
