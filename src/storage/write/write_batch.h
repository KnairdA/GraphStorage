#ifndef GRAPHDB_SRC_STORAGE_WRITE_WRITE_BATCH_H_
#define GRAPHDB_SRC_STORAGE_WRITE_WRITE_BATCH_H_

#include <vector>
#include <memory>

#include "leveldb/write_batch.h"

#include "storage/property_value.h"
#include "storage/storage_facade.h"
#include "storage/query/edge_stream_distributor.h"

namespace GraphDB {

class WriteBatch {
	public:
		typedef std::unique_ptr<WriteBatch> Ptr;

		virtual ~WriteBatch();

		void commit(StorageFacade&, EdgeStreamDistributor&);

	protected:
		template <class Key>
		void set(const Key&, const PropertyValue&);
		template <class Key>
		void set(const Key&);
		template <class Key>
		void remove(const Key&);

		leveldb::WriteBatch batch_;
		std::vector<EdgeStreamEvent> event_queue_;

};

}

#endif  // GRAPHDB_SRC_STORAGE_WRITE_WRITE_BATCH_H_
