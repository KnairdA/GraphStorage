#include <iostream>

#include "graph_storage.h"
#include "query/logic/logic_and_iterator.h"
#include "query/logic/logic_or_iterator.h"
#include "storage/query/edge_iterator.h"
#include "storage/query/property_iterator.h"

int main() {
	GraphDB::GraphStorage storage("./testdb");

	GraphDB::QueryState::Ptr state = storage.getQueryState();
	GraphDB::PropertyValue value;

	GraphDB::LogicIterator::Ptr andIter = storage.getIterator<GraphDB::LogicAndIterator>(state.get());
	GraphDB::PropertyIterator* nameIter = andIter->getIterator<GraphDB::PropertyIterator>((uint16_t) 1);

	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 0, (uint16_t) 1,  GraphDB::EdgeDirection::Outbound);
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 3015959, (uint16_t) 4, GraphDB::EdgeDirection::Outbound);

	GraphDB::LogicIterator* orIter = andIter->getIterator<GraphDB::LogicOrIterator>();
	orIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 2972042, (uint16_t) 4, GraphDB::EdgeDirection::Outbound);
	orIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 2984160, (uint16_t) 4, GraphDB::EdgeDirection::Outbound);

	while ( andIter->hasNext() ) {
		nameIter->getCurrentValue(value);
		std::cout << static_cast<std::string>(value) << std::endl;

		andIter->getNext();
	}

	google::protobuf::ShutdownProtobufLibrary();
}
