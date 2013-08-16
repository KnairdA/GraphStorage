#ifndef GRAPHDB_SRC_STORAGE_ID_EDGE_ID_H_
#define GRAPHDB_SRC_STORAGE_ID_EDGE_ID_H_

#include <cstdint>
#include <cstddef>

#include "storage/storage_guard.h"
#include "storage/buffer_utils.h"

namespace GraphDB {

struct EdgeId {
	static void toBuffer(const EdgeId&, BufferGuard<EdgeId>&);
	static bool fromBuffer(EdgeId&, const void*);
	static bool equalArea(const EdgeId&, const EdgeId&);

	EdgeId();
	EdgeId(uint32_t, uint16_t, EdgeDirection, uint32_t);
	EdgeId(const void* keyBuffer);

	bool operator==(const EdgeId&);

	static const StorageSection Section = StorageSection::Edge;
	static const size_t Size = sizeof(StorageSection) + 
	                           sizeof(uint32_t)       +
	                           sizeof(uint16_t)       +
	                           sizeof(EdgeDirection)  +
	                           sizeof(uint32_t);

	uint32_t fromId;
	uint16_t typeId;
	EdgeDirection direction;
	uint32_t toId;
};

}

#endif  // GRAPHDB_SRC_STORAGE_ID_EDGE_ID_H_
