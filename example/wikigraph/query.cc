#include <iostream>

#include "graph_storage.h"
#include "query/logic/logic_and_iterator.h"
#include "query/logic/logic_or_iterator.h"
#include "storage/query/storage_iterator.h"

int main() {
	GraphDB::GraphStorage storage("./testdb");

	GraphDB::QueryState::Ptr state = storage.getQueryState();
	GraphDB::PropertyValue value;

	GraphDB::LogicIterator::Ptr andIter = storage.getIterator<GraphDB::LogicAndIterator>(state.get());
	GraphDB::PropertyIterator* nameIter = andIter->getIterator<GraphDB::PropertyIterator>(
		GraphDB::NodePropertyId(1, 0)
	);

	andIter->getIterator<GraphDB::EdgeIterator>(
		GraphDB::EdgeId(0, 1, GraphDB::EdgeDirection::Outbound, 0)
	);
	andIter->getIterator<GraphDB::EdgeIterator>(
		GraphDB::EdgeId(3015959, 4, GraphDB::EdgeDirection::Outbound, 0)
	);

	GraphDB::LogicIterator* orIter = andIter->getIterator<GraphDB::LogicOrIterator>();

	orIter->getIterator<GraphDB::EdgeIterator>(
		GraphDB::EdgeId(2972042, 4, GraphDB::EdgeDirection::Outbound, 0)
	);
	orIter->getIterator<GraphDB::EdgeIterator>(
		GraphDB::EdgeId(2984160, 4, GraphDB::EdgeDirection::Outbound, 0)
	);

	while ( andIter->hasNext() ) {
		nameIter->getCurrentValue(value);
		std::cout << static_cast<std::string>(value) << std::endl;

		andIter->getNext();
	}

	google::protobuf::ShutdownProtobufLibrary();
}
