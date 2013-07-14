#include "storage/write/maintenance_buffer.h"

namespace GraphDB {

void MaintenanceBuffer::createNode(uint32_t id) {
	EdgeId edge(0, 1, EdgeDirection::Outbound, id);

	this->set<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::INSERT, edge)
	);
}

void MaintenanceBuffer::discardNode(uint32_t id) {
	EdgeId edge(0, 1, EdgeDirection::Outbound, id);

	this->remove<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::REMOVE, edge)
	);

	edge.typeId = 2;

	this->set<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::INSERT, edge)
	);
}

}
