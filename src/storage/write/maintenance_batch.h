#ifndef GRAPHDB_SRC_STORAGE_WRITE_MAINTENANCE_BATCH_H_
#define GRAPHDB_SRC_STORAGE_WRITE_MAINTENANCE_BATCH_H_

#include "storage/storage_guard.h"
#include "storage/write/write_batch.h"
#include "storage/id/identifier_id.h"

namespace GraphDB {

class MaintenanceBatch : public WriteBatch {
	public:
		typedef std::unique_ptr<MaintenanceBatch> Ptr;

		void createNode(uint32_t);
		void discardNode(uint32_t);

		template <IdentifierType KeyType, typename ValueType>
		void setIdentifier(std::string, ValueType, PropertyValue&);

};

template <IdentifierType KeyType, typename ValueType>
void MaintenanceBatch::setIdentifier(std::string name,
                                      ValueType value,
                                      PropertyValue& property) {
	property = static_cast<uint64_t>(value);
	this->set<IdentifierId>(
		IdentifierId(KeyType, name),
		property
	);
}

}

#endif  // GRAPHDB_SRC_STORAGE_WRITE_MAINTENANCE_BATCH_H_
