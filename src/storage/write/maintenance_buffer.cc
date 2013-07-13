#include "storage/write/maintenance_buffer.h"

namespace GraphDB {

void MaintenanceBuffer::createNode(uint32_t id) {
	this->set<EdgeId>(
		EdgeId(0, 1, EdgeDirection::Outbound, id)
	);
}

void MaintenanceBuffer::discardNode(uint32_t id) {
	this->set<EdgeId>(
		EdgeId(0, 2, EdgeDirection::Outbound, id)
	);
	this->WriteBuffer::remove<EdgeId>(
		EdgeId(0, 1, EdgeDirection::Outbound, id)
	);
}

}
