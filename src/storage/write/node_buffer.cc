#include "storage/write/node_buffer.h"

#include "storage/id/edge_id.h"
#include "storage/id/node_property_id.h"

namespace GraphDB {

NodeBuffer::NodeBuffer(BasicIterator* const iter):
	iterator_(iter) { }

uint32_t NodeBuffer::getCurrent() {
	return this->iterator_->getCurrent();
}

void NodeBuffer::create() {
	EdgeId edge(0, 1, EdgeDirection::Outbound, this->getCurrent());

	this->set<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::INSERT, edge)
	);
}

void NodeBuffer::discard() {
	EdgeId edge(0, 1, EdgeDirection::Outbound, this->getCurrent());

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

void NodeBuffer::connectTo(uint32_t toId, uint16_t typeId) {
	EdgeId edge(this->getCurrent(), typeId, EdgeDirection::Outbound, toId);

	this->set<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::INSERT, edge)
	);

	edge.direction = EdgeDirection::Inbound;

	this->set<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::INSERT, edge)
	);
}

void NodeBuffer::disconnectFrom(uint32_t toId, uint16_t typeId) {
	EdgeId edge(this->getCurrent(), typeId, EdgeDirection::Outbound, toId);

	this->remove<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::REMOVE, edge)
	);

	edge.direction = EdgeDirection::Inbound;

	this->remove<EdgeId>(edge);
	this->event_queue_.push_back(
		EdgeStreamEvent(EdgeStreamEventType::REMOVE, edge)
	);
}

void NodeBuffer::setProperty(uint16_t propertyId, const PropertyValue& value) {
	this->set<NodePropertyId>(
		NodePropertyId(this->getCurrent(), propertyId),
		value
	);
}

void NodeBuffer::removeProperty(uint16_t propertyId) {
	this->remove<NodePropertyId>(
		NodePropertyId(this->getCurrent(), propertyId)
	);
}

}
