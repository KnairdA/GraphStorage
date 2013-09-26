#include "storage/write/node_batch.h"

#include "storage/id/edge_id.h"
#include "storage/id/node_property_id.h"

namespace GraphDB {

NodeBatch::NodeBatch(BasicIterator* const iter, bool events):
	iterator_(iter),
	events_(events) { }

uint32_t NodeBatch::getCurrent() {
	return this->iterator_->getCurrent();
}

void NodeBatch::create() {
	EdgeId edge(0, 1, EdgeDirection::Outbound, this->getCurrent());

	this->set<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::INSERT, edge);
}

void NodeBatch::discard() {
	EdgeId edge(0, 1, EdgeDirection::Outbound, this->getCurrent());

	this->remove<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::REMOVE, edge);

	edge.typeId = 2;

	this->set<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::INSERT, edge);
}

void NodeBatch::connectTo(uint32_t toId, uint16_t typeId) {
	EdgeId edge(this->getCurrent(), typeId, EdgeDirection::Outbound, toId);

	this->set<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::INSERT, edge);

	edge.fromId    = toId;
	edge.direction = EdgeDirection::Inbound;
	edge.nodeId    = this->getCurrent();

	this->set<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::INSERT, edge);
}

void NodeBatch::disconnectFrom(uint32_t toId, uint16_t typeId) {
	EdgeId edge(this->getCurrent(), typeId, EdgeDirection::Outbound, toId);

	this->remove<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::REMOVE, edge);

	edge.fromId    = toId;
	edge.direction = EdgeDirection::Inbound;
	edge.nodeId    = this->getCurrent();

	this->remove<EdgeId>(edge);
	this->addEvent(EdgeStreamEventType::REMOVE, edge);
}

void NodeBatch::setProperty(uint16_t propertyId, const PropertyValue& value) {
	this->set<NodePropertyId>(
		NodePropertyId(propertyId, this->getCurrent()),
		value
	);
}

void NodeBatch::removeProperty(uint16_t propertyId) {
	this->remove<NodePropertyId>(
		NodePropertyId(propertyId, this->getCurrent())
	);
}

void NodeBatch::addEvent(EdgeStreamEventType type, EdgeId& edge) {
	if ( this->events_ ) {
		this->event_queue_.push_back(EdgeStreamEvent(type, edge));
	}
}

}
