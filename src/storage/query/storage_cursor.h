#ifndef GRAPHDB_SRC_STORAGE_QUERY_STORAGE_CURSOR_H_
#define GRAPHDB_SRC_STORAGE_QUERY_STORAGE_CURSOR_H_

#include <memory>

#include "leveldb/db.h"

#include "storage/property_value.h"
#include "storage/buffer_utils.h"
#include "storage/protobuf/storage_record.pb.h"

namespace GraphDB {

template <typename Key>
class StorageCursor {
	public:
		typedef typename std::unique_ptr<StorageCursor<Key>> Ptr;

		StorageCursor(std::unique_ptr<leveldb::Iterator>);

		bool jump(const Key&);

		Key getCurrent();
		Key getNext();
		bool hasNext();

		void getCurrentValue(PropertyValue&);

	private:
		bool jumpApproximately(const Key&);
		void step();

		std::unique_ptr<leveldb::Iterator> cursor_;
		BufferGuard key_buffer_;
		Key curr_key_;
		bool has_next_;

};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_STORAGE_CURSOR_H_
