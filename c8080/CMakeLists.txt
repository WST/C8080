# Название проекта, минимально требуемая версия CMake, стандарт C++ (включить если понадобится)
cmake_minimum_required(VERSION 3.1)
project(vrcc) # vinxru C compiler
set(CMAKE_CXX_STANDARD 11)

# Исходники и заголовочные файлы проекта
FILE(GLOB VRCC_SOURCE src/*.cpp)
include_directories("." "src/")

add_executable(vrcc ${VRCC_SOURCE})
#target_link_libraries(ots-controller ${LibMayCloud_LIBRARIES} udns expat ${MYSQL_LIBRARY})

# Реализация кастомной цели distclean
ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
set(DISTCLEANED CMakeCache.txt CMakeFiles cmake_install.cmake Makefile vrcc install_manifest_vrcc.txt)
ADD_CUSTOM_COMMAND (
	DEPENDS clean
	COMMENT "distribution clean"
	COMMAND rm
	ARGS -Rf ${DISTCLEANED}
	TARGET  distclean
)
