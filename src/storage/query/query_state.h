#ifndef GRAPHDB_SRC_STORAGE_QUERY_QUERY_STATE_H_
#define GRAPHDB_SRC_STORAGE_QUERY_QUERY_STATE_H_

#include <memory>

#include "leveldb/db.h"

namespace GraphDB {

class StorageGuard;

class QueryState {
	public:
		typedef std::unique_ptr<QueryState> Ptr;

		QueryState(const StorageGuard&);
		~QueryState();

		const leveldb::Snapshot* getState() const;
		leveldb::ReadOptions getReadOptions() const;

	private:
		leveldb::DB* const db_;
		const leveldb::Snapshot* state_;

};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_QUERY_STATE_H_
