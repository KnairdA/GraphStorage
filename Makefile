CXX      = g++
CXXFLAGS = -g -W -Wall -Wextra -pedantic -std=c++11 -fpic -Isrc

SRC_DIR                 = src
STORAGE_DIR             = $(SRC_DIR)/storage
STORAGE_QUERY_DIR       = $(STORAGE_DIR)/query
STORAGE_PROTOBUF_DIR    = $(STORAGE_DIR)/protobuf
STORAGE_WRITE_DIR       = $(STORAGE_DIR)/write
QUERY_DIR               = $(SRC_DIR)/query
QUERY_LOGIC_DIR         = $(QUERY_DIR)/logic

STORAGE_SRC             = $(STORAGE_DIR)/storage_guard.cc \
                          $(STORAGE_DIR)/buffer_utils.cc \
                          $(STORAGE_DIR)/storage_facade.cc \
                          $(STORAGE_DIR)/id/edge_id.cc \
                          $(STORAGE_DIR)/id/identifier_id.cc \
                          $(STORAGE_DIR)/id/node_property_id.cc \
                          $(STORAGE_DIR)/property_value.cc
STORAGE_PROTOBUF_SRC    = $(STORAGE_PROTOBUF_DIR)/storage_record.pb.cc
STORAGE_QUERY_SRC       = $(STORAGE_QUERY_DIR)/query_state.cc \
                          $(STORAGE_QUERY_DIR)/storage_cursor.cc \
                          $(STORAGE_QUERY_DIR)/edge_iterator.cc \
                          $(STORAGE_QUERY_DIR)/property_iterator.cc \
                          $(STORAGE_QUERY_DIR)/edge_stream_distributor.cc \
                          $(STORAGE_QUERY_DIR)/edge_stream_pattern.cc \
                          $(STORAGE_QUERY_DIR)/edge_subscription.cc
STORAGE_WRITE_SRC       = $(STORAGE_WRITE_DIR)/write_batch.cc \
                          $(STORAGE_WRITE_DIR)/maintenance_batch.cc \
                          $(STORAGE_WRITE_DIR)/node_batch.cc 
QUERY_SRC               = $(QUERY_DIR)/logic_iterator.cc \
                          $(QUERY_DIR)/dummy_iterator.cc \
                          $(QUERY_DIR)/logic_subscription.cc \
                          $(QUERY_DIR)/edge_subscription_printer.cc
QUERY_LOGIC_SRC         = $(QUERY_LOGIC_DIR)/logic_and_iterator.cc \
                          $(QUERY_LOGIC_DIR)/logic_or_iterator.cc \
                          $(QUERY_LOGIC_DIR)/logic_xor_iterator.cc \
                          $(QUERY_LOGIC_DIR)/logic_and_subscription.cc \
                          $(QUERY_LOGIC_DIR)/logic_or_subscription.cc \
                          $(QUERY_LOGIC_DIR)/logic_xor_subscription.cc
GRAPH_STORAGE_SRC       = $(SRC_DIR)/graph_storage.cc

SRC = $(STORAGE_SRC) \
      $(STORAGE_PROTOBUF_SRC) \
      $(STORAGE_QUERY_SRC) \
      $(STORAGE_WRITE_SRC) \
      $(QUERY_SRC) \
      $(QUERY_LOGIC_SRC) \
      $(GRAPH_STORAGE_SRC)

OBJ = $(subst .cc,.o,$(SRC))

all: dev

dev: $(OBJ)
	$(CXX) -shared -o libGraphStorage.so $(OBJ) $(CXXFLAGS) 

depend: .depend

.depend: $(SRC)
	$(CXX) -M $(CXXFLAGS) $< > $@

clean:
	rm -f $(OBJ)

include .depend
