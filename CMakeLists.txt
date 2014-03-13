cmake_minimum_required(VERSION 2.8)
project(GraphStorage)

set(
	CMAKE_CXX_FLAGS
	"-std=c++11 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	src/
)

add_library(
	GraphStorage
	SHARED
	src/storage/storage_guard.cc
	src/storage/buffer_utils.cc
	src/storage/storage_facade.cc
	src/storage/id/edge_id.cc
	src/storage/id/identifier_id.cc
	src/storage/id/node_property_id.cc
	src/storage/property_value.cc
	src/storage/protobuf/storage_record.pb.cc
	src/storage/query/query_state.cc
	src/storage/query/storage_cursor.cc
	src/storage/query/storage_iterator.cc
	src/storage/query/edge_stream_distributor.cc
	src/storage/query/edge_stream_pattern.cc
	src/storage/query/edge_subscription.cc
	src/storage/write/write_batch.cc
	src/storage/write/maintenance_batch.cc
	src/storage/write/node_batch.cc
	src/query/logic_iterator.cc
	src/query/dummy_iterator.cc
	src/query/logic_subscription.cc
	src/query/logic/logic_and_iterator.cc
	src/query/logic/logic_or_iterator.cc
	src/query/logic/logic_xor_iterator.cc
	src/query/logic/logic_and_subscription.cc
	src/query/logic/logic_or_subscription.cc
	src/query/logic/logic_xor_subscription.cc
	src/graph_storage.cc
)

install(
	TARGETS
	GraphStorage
	LIBRARY DESTINATION
	/usr/lib
)
