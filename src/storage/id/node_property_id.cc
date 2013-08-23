#include "storage/id/node_property_id.h"
#include "exceptions.h"

namespace GraphDB {

void NodePropertyId::toBuffer(const NodePropertyId& id,
                              BufferGuard<NodePropertyId>& keyBuffer) {
	writeNumber<uint8_t>(
		reinterpret_cast<uint8_t*>(keyBuffer.data)+0, NodePropertyId::Section
	);
	writeNumber<uint16_t>(
		reinterpret_cast<uint8_t*>(keyBuffer.data)+1, id.propertyId
	);
	writeNumber<uint32_t>(
		reinterpret_cast<uint8_t*>(keyBuffer.data)+3, id.nodeId
	);
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

bool NodePropertyId::equalArea(const NodePropertyId& id1,
                               const NodePropertyId& id2) {
	return id1.propertyId == id2.propertyId;
}

NodePropertyId::NodePropertyId() { }

NodePropertyId::NodePropertyId(uint16_t property, uint32_t node):
	propertyId(property),
	nodeId(node) { }

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
