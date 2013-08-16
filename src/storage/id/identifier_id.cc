#include "storage/id/identifier_id.h"
#include "exceptions.h"

namespace GraphDB {

void IdentifierId::toBuffer(const IdentifierId& id,
                            BufferGuard<IdentifierId>& keyBuffer) {
	keyBuffer.resize(IdentifierId::Size + id.name.length() + 1);

	writeNumber<uint8_t>(
		reinterpret_cast<uint8_t*>(keyBuffer.data)+0, IdentifierId::Section
	);
	writeNumber<uint8_t>(
		reinterpret_cast<uint8_t*>(keyBuffer.data)+1, id.type
	);
	writeString(
		reinterpret_cast<uint8_t*>(keyBuffer.data)+2, id.name
	);
}

inline static bool checkStorageSection(const void* keyBuffer) {
	return (StorageSection::Identifier == readNumber<uint8_t>(
		reinterpret_cast<const uint8_t*>(keyBuffer)+0
	));
}

bool IdentifierId::fromBuffer(IdentifierId& id, const void* keyBuffer) {
	if ( checkStorageSection(keyBuffer) ) {
		id.type = static_cast<IdentifierType>(readNumber<uint8_t>(
			reinterpret_cast<const uint8_t*>(keyBuffer)+1
		));
		id.name = readString(
			reinterpret_cast<const uint8_t*>(keyBuffer)+2
		);

		return true;
	} else {
		return false;
	}
}

bool IdentifierId::equalArea(const IdentifierId& id1,
                             const IdentifierId& id2) {
	return id1.type == id2.type;
}

IdentifierId::IdentifierId() { }

IdentifierId::IdentifierId(IdentifierType itype, std::string iname):
	type(itype),
	name(iname) { }

IdentifierId::IdentifierId(const void* keyBuffer) {
	if ( IdentifierId::fromBuffer(*this, keyBuffer) ) {
		throw storage_section_exception();
	}
}

bool IdentifierId::operator==(const IdentifierId& refId) {
	return type == refId.type &&
	       name == refId.name;
}

}
