#include <iostream>
#include <vector>
#include <memory>

#include "exceptions.h"
#include "graph_storage.h"

#include "query/logic/logic_and_iterator.h"
#include "query/logic/logic_or_iterator.h"
#include "query/logic/logic_xor_iterator.h"
#include "storage/query/edge_iterator.h"

int main() {
	GraphDB::GraphStorage storage("./testdb");

	GraphDB::QueryState::Ptr state = storage.getQueryState();

	GraphDB::LogicIterator::Ptr andIter = storage.getIterator<GraphDB::LogicAndIterator>(state.get());
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 0, (uint16_t) 1,  GraphDB::EdgeDirection::Outbound);
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 1, (uint16_t) 10, GraphDB::EdgeDirection::Outbound);

	GraphDB::LogicIterator *orIter = andIter->getIterator<GraphDB::LogicOrIterator>();
	orIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 2, (uint16_t) 25, GraphDB::EdgeDirection::Outbound);
	orIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 3, (uint16_t) 20, GraphDB::EdgeDirection::Outbound);

	while ( andIter->hasNext() ) {
		std::cout << andIter->getCurrent() << std::endl;

		andIter->getNext();
	}

	google::protobuf::ShutdownProtobufLibrary();
}
