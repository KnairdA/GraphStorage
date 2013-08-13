#include "storage/id/edge_id.h"
#include "exceptions.h"

namespace GraphDB {

BufferGuard::Ptr EdgeId::toBuffer(const EdgeId& id) {
	BufferGuard::Ptr keyBuffer(new BufferGuard(EdgeId::Size));

	writeNumber<uint8_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+0, EdgeId::Section
	);
	writeNumber<uint32_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+1, id.fromId
	);
	writeNumber<uint16_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+5, id.typeId
	);
	writeNumber<uint8_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+7, id.direction
	);
	writeNumber<uint32_t>(
		reinterpret_cast<uint8_t*>(keyBuffer->data)+8, id.toId
	);

	return keyBuffer;
}

void EdgeId::toBuffer(const EdgeId& id, BufferGuard& keyBuffer) {
	if ( keyBuffer.size == EdgeId::Size ) {
		writeNumber<uint8_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+0, EdgeId::Section
		);
		writeNumber<uint32_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+1, id.fromId
		);
		writeNumber<uint16_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+5, id.typeId
		);
		writeNumber<uint8_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+7, id.direction
		);
		writeNumber<uint32_t>(
			reinterpret_cast<uint8_t*>(keyBuffer.data)+8, id.toId
		);
	} else {
		throw buffer_size_exception();
	}
}

inline static bool checkStorageSection(const void* keyBuffer) {
	return (EdgeId::Section == readNumber<uint8_t>(
		reinterpret_cast<const uint8_t*>(keyBuffer)+0
	));
}

bool EdgeId::fromBuffer(EdgeId& id, const void* keyBuffer) {
	if ( checkStorageSection(keyBuffer) ) {
		id.fromId    = readNumber<uint32_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+1
		);
		id.typeId    = readNumber<uint16_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+5
		);
		id.direction = static_cast<EdgeDirection>(readNumber<uint8_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+7
		));
		id.toId      = readNumber<uint32_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+8
		);

		return true;
	} else {
		return false;
	}
}

EdgeId::EdgeId() { }

EdgeId::EdgeId(uint32_t from,
               uint16_t type,
               EdgeDirection dir,
               uint32_t to):
	fromId(from),
	typeId(type),
	direction(dir),
	toId(to) { }

EdgeId::EdgeId(const void* keyBuffer) {
	if ( EdgeId::fromBuffer(*this, keyBuffer) ) {
		throw storage_section_exception();
	}
}

bool EdgeId::operator==(const EdgeId& refId) {
	return fromId    == refId.fromId    &&
	       typeId    == refId.typeId    &&
	       direction == refId.direction &&
	       toId      == refId.toId;
}

}
