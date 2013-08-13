#ifndef GRAPHDB_SRC_STORAGE_ID_NODE_PROPERTY_ID_H_
#define GRAPHDB_SRC_STORAGE_ID_NODE_PROPERTY_ID_H_

#include <cstdint>
#include <cstddef>

#include "storage/storage_guard.h"
#include "storage/buffer_utils.h"

namespace GraphDB {

struct NodePropertyId {
	static BufferGuard::Ptr toBuffer(const NodePropertyId&);
	static void toBuffer(const NodePropertyId&, BufferGuard&);
	static bool fromBuffer(NodePropertyId&, const void* keyBuffer);

	NodePropertyId();
	NodePropertyId(uint32_t, uint16_t);
	NodePropertyId(const void* keyBuffer);

	bool operator==(const NodePropertyId&);

	static const StorageSection Section = StorageSection::NodeProperty;
	static const size_t Size = sizeof(StorageSection) + 
	                           sizeof(uint16_t)       +
	                           sizeof(uint32_t);

	uint32_t nodeId;
	uint16_t propertyId;

};

}

#endif  // GRAPHDB_SRC_STORAGE_ID_NODE_PROPERTY_ID_H_
