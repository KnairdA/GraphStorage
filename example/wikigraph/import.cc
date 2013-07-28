#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "graph_storage.h"
#include "query/dummy_iterator.h"
#include "storage/write/node_batch.h"

void splitLine(const std::string &line,
               char delimiter,
               std::vector<std::string> &elements) {
	std::stringstream stream(line);
	std::string item;

	while ( std::getline(stream, item, delimiter) ) {
		elements.emplace_back(item);
	}
}

void importGraph(GraphDB::GraphStorage& storage, std::string datasetPath) {
	uint32_t importedNodes = 0;
	uint32_t importedLinks = 0;

	GraphDB::QueryState::Ptr state(storage.getQueryState());
	std::ifstream rawLinks(datasetPath);

	uint32_t nodeId;
	std::string line;
	std::vector<std::string> lineElements;

	GraphDB::DummyIterator::Ptr batchPosition(
		storage.getIterator<GraphDB::DummyIterator>(state.get())
	);

	while ( std::getline(rawLinks, line) ) {
		GraphDB::NodeBatch batch(batchPosition.get(), false);

		lineElements.clear();

		splitLine(line, ':', lineElements);

		std::istringstream nodeCast(lineElements[0]);
		nodeCast >> nodeId;

		batchPosition->jumpTo(nodeId);

		batch.create();
		importedNodes++;

		line = lineElements[1];
		lineElements.clear();

		splitLine(line, ' ', lineElements);

		for ( uint32_t i = 1; i < lineElements.size(); i++ ) {
			std::istringstream linkCast(lineElements[i]);
			linkCast >> nodeId;

			batch.connectTo(nodeId, 4);
			importedLinks++;
		}

		storage.commitBatch(&batch);
	}

	std::cout << "Imported " << importedNodes << " nodes" << std::endl;
	std::cout << "Imported " << importedLinks << " links" << std::endl;
}

void importTitles(GraphDB::GraphStorage& storage, std::string datasetPath) {
	GraphDB::QueryState::Ptr state(storage.getQueryState());
	std::ifstream rawLinks(datasetPath);

	std::string line;

	GraphDB::PropertyValue value;
	GraphDB::DummyIterator::Ptr batchPosition(
		storage.getIterator<GraphDB::DummyIterator>(state.get())
	);
	batchPosition->jumpTo(1);

	while ( std::getline(rawLinks, line) ) {
		GraphDB::NodeBatch batch(batchPosition.get(), false);

		value = line;
		batch.setProperty(1, value);

		storage.commitBatch(&batch);

		batchPosition->getNext();
	}

	std::cout << "Imported " << batchPosition->getCurrent()-1 << " node titles" << std::endl;
}

int main() {
	GraphDB::GraphStorage storage("./testdb");

	importGraph(storage, "./dataset/links-simple-sorted.txt");
	importTitles(storage, "./dataset/titles-sorted.txt");

	google::protobuf::ShutdownProtobufLibrary();
}
