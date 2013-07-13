#ifndef GRAPHDB_SRC_STORAGE_ID_IDENTIFIER_ID_H_
#define GRAPHDB_SRC_STORAGE_ID_IDENTIFIER_ID_H_

#include <cstdint>
#include <cstddef>

#include "storage/storage_guard.h"
#include "storage/buffer_utils.h"

namespace GraphDB {

struct IdentifierId {
	static BufferGuard::Ptr toBuffer(const IdentifierId&);
	static bool fromBuffer(IdentifierId&, const void* keyBuffer);

	IdentifierId();
	IdentifierId(IdentifierType, std::string);
	IdentifierId(const void* keyBuffer);

	bool operator==(const IdentifierId&);

	static const StorageSection Section = StorageSection::Identifier;
	static const size_t Size = sizeof(StorageSection) + 
	                           sizeof(IdentifierType);

	IdentifierType type;
	std::string name;
};

}

#endif  // GRAPHDB_SRC_STORAGE_ID_IDENTIFIER_ID_H_
