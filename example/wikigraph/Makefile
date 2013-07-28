CXX      = g++
CXXFLAGS = -g -W -Wall -Wextra -pedantic -std=c++11 -I../../src/
LDLIBS   = -L. -lGraphStorage -lleveldb -lprotobuf -ltcmalloc

IMPORT_SRC = import.cc 
QUERY_SRC  = query.cc 

IMPORT_OBJ = $(subst .cc,.o,$(IMPORT_SRC))
QUERY_OBJ  = $(subst .cc,.o,$(QUERY_SRC))

all: import query

import: $(IMPORT_OBJ)
	$(CXX) -o import $(IMPORT_OBJ) $(CXXFLAGS) $(LDLIBS)

query: $(QUERY_OBJ)
	$(CXX) -o query $(QUERY_OBJ) $(CXXFLAGS) $(LDLIBS)

depend: .depend

.depend: $(IMPORT_SRC) $(QUERY_SRC)
	$(CXX) -M $(CXXFLAGS) $(LDLIBS) $< > $@

clean:
	rm -f $(IMPORT_OBJ)
	rm -f $(QUERY_OBJ)

include .depend
