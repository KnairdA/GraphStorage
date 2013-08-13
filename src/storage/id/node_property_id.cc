#include "storage/id/node_property_id.h"
#include "exceptions.h"

namespace GraphDB {

BufferGuard::Ptr NodePropertyId::toBuffer(const NodePropertyId& id) {
	BufferGuard::Ptr keyBuffer(new BufferGuard(NodePropertyId::Size));

	writeNumber<uint8_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+0, NodePropertyId::Section
	);
	writeNumber<uint16_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+1, id.propertyId
	);
	writeNumber<uint32_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+3, id.nodeId
	);

	return keyBuffer;
}

void NodePropertyId::toBuffer(const NodePropertyId& id,
                              BufferGuard& keyBuffer) {
	if ( keyBuffer.size == NodePropertyId::Size ) {
		writeNumber<uint8_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+0, NodePropertyId::Section
		);
		writeNumber<uint16_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+1, id.propertyId
		);
		writeNumber<uint32_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+3, id.nodeId
		);
	} else {
		throw buffer_size_exception();
	}
}

inline static bool checkStorageSection(const void* keyBuffer) {
	return (NodePropertyId::Section == readNumber<uint8_t>(
		reinterpret_cast<const uint8_t*>(keyBuffer)+0
	));
}

bool NodePropertyId::fromBuffer(NodePropertyId& id, const void* keyBuffer) {
	if ( checkStorageSection(keyBuffer) ) {
		id.propertyId = readNumber<uint16_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+1
		);
		id.nodeId     = readNumber<uint32_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+3
		);

		return true;
	} else {
		return false;
	}
}

NodePropertyId::NodePropertyId() { }

NodePropertyId::NodePropertyId(uint32_t node, uint16_t property):
	nodeId(node),
	propertyId(property) { }

NodePropertyId::NodePropertyId(const void* keyBuffer) {
	if ( NodePropertyId::fromBuffer(*this, keyBuffer) ) {
		throw storage_section_exception();
	}
}

bool NodePropertyId::operator==(const NodePropertyId& refId) {
	return nodeId     == refId.nodeId &&
	       propertyId == refId.propertyId;
}

}
