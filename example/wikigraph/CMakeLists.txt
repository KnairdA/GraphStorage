cmake_minimum_required(VERSION 2.8)
project(WikiGraph)

set(
	CMAKE_CXX_FLAGS
	"-std=c++11 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	../../src/
)

add_subdirectory(
	../../
	../../../build/
)

add_executable(
	import
	import.cc
)

add_executable(
	query
	query.cc
)

target_link_libraries(
	import
	GraphStorage
	leveldb
	protobuf
	tcmalloc
)

target_link_libraries(
	query
	GraphStorage
	leveldb
	protobuf
	tcmalloc
)
