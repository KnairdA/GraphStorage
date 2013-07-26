#include <iostream>
#include <vector>
#include <memory>

#include <fstream>
#include <sstream>

#include "exceptions.h"
#include "graph_storage.h"

#include "query/dummy_iterator.h"
#include "query/logic/logic_and_iterator.h"
#include "query/logic/logic_or_iterator.h"
#include "query/logic/logic_xor_iterator.h"
#include "storage/query/edge_iterator.h"
#include "storage/query/property_iterator.h"

std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while ( std::getline(ss, item, delim) ) {
        elems.push_back(item);
    }

    return elems;
}

int main() {
	GraphDB::GraphStorage storage("./testdb");

	/*GraphDB::QueryState::Ptr state = storage.getQueryState();

	std::ifstream file("/home/adrian/tmp/wikidump/titles-sorted.txt");
	std::string line;

	GraphDB::PropertyValue value;
	GraphDB::DummyIterator::Ptr iter = storage.getIterator<GraphDB::DummyIterator>(state.get());

	while ( std::getline(file, line) ) {
		GraphDB::NodeBuffer buffer(iter.get());
		buffer.create();

		value = line;
		buffer.setProperty(1, value);

		storage.commitBuffer(&buffer);
		std::cout << line << std::endl;

		iter->getNext();
	}*/

	GraphDB::QueryState::Ptr state = storage.getQueryState();
	GraphDB::PropertyValue value;

	GraphDB::LogicIterator::Ptr andIter = storage.getIterator<GraphDB::LogicAndIterator>(state.get());
	GraphDB::PropertyIterator* nameIter = andIter->getIterator<GraphDB::PropertyIterator>((uint16_t) 1);

	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 0, (uint16_t) 1,  GraphDB::EdgeDirection::Outbound);
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 3015959, (uint16_t) 7, GraphDB::EdgeDirection::Outbound);
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 5538194, (uint16_t) 7, GraphDB::EdgeDirection::Outbound);

	while ( andIter->hasNext() ) {
		nameIter->getCurrentValue(value);
		std::cout << static_cast<std::string>(value) << std::endl;

		andIter->getNext();
	}

	/*GraphDB::QueryState::Ptr state = storage.getQueryState();

	std::ifstream file("/home/adrian/tmp/wikidump/links-simple-sorted.txt");
	std::string line;

	std::vector<std::string> elems;
	std::string links;

	GraphDB::DummyIterator::Ptr iter = storage.getIterator<GraphDB::DummyIterator>(state.get());

	while ( std::getline(file, line) ) {
		elems.clear();

		split(line, ':', elems);

		GraphDB::NodeBuffer buffer(iter.get());
		uint32_t id;

		std::istringstream convertStream(elems[0]);
		convertStream >> id;

		iter->jumpTo(id);
		buffer.create();

		links = elems[1];
		elems.clear();

		split(links, ' ', elems);

		for ( uint32_t i = 1; i < elems.size(); i++ ) {
			std::istringstream converter(elems[i]);
			converter >> id;

			buffer.connectTo(id, 7);
		}

		storage.commitBuffer(&buffer);
	}*/

	/*GraphDB::QueryState::Ptr state = storage.getQueryState();

	GraphDB::LogicIterator::Ptr andIter = storage.getIterator<GraphDB::LogicAndIterator>(state.get());
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 0, (uint16_t) 1,  GraphDB::EdgeDirection::Outbound);
	andIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 1, (uint16_t) 10, GraphDB::EdgeDirection::Outbound);

	GraphDB::LogicIterator *orIter = andIter->getIterator<GraphDB::LogicOrIterator>();
	orIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 2, (uint16_t) 25, GraphDB::EdgeDirection::Outbound);
	orIter->getIterator<GraphDB::EdgeIterator>((uint32_t) 3, (uint16_t) 20, GraphDB::EdgeDirection::Outbound);

	while ( andIter->hasNext() ) {
		std::cout << andIter->getCurrent() << std::endl;

		andIter->getNext();
	}*/

	google::protobuf::ShutdownProtobufLibrary();
}
