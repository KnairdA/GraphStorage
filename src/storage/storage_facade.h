#ifndef GRAPHDB_SRC_STORAGE_STORAGE_FACADE_H_
#define GRAPHDB_SRC_STORAGE_STORAGE_FACADE_H_

#include <cstdint>
#include <memory>

#include "leveldb/write_batch.h"

#include "storage/storage_guard.h"
#include "storage/query/storage_cursor.h"

namespace GraphDB {

class StorageFacade {
	public:
		explicit StorageFacade(StorageGuard&);

		template <class Key>
		typename StorageCursor<Key>::Ptr getCursor(const Key&,
		                                           const QueryState*) const;

		void commitBatch(leveldb::WriteBatch&);

		template <class Key>
		bool get(const Key&, PropertyValue&) const;
		template <class Key>
		bool check(const Key&) const;
		template <class Key>
		void set(const Key&, const PropertyValue&);
		template <class Key>
		void set(const Key&);
		template <class Key>
		void remove(const Key&);

	private:
		template <class Key>
		std::unique_ptr<leveldb::Iterator> getInternalCursor(
			const Key&,
			const leveldb::ReadOptions&) const;

		leveldb::DB* const db_;

};

}

#endif  // GRAPHDB_SRC_STORAGE_STORAGE_FACADE_H_
