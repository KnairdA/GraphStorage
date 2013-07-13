#ifndef GRAPHDB_SRC_STORAGE_STORAGE_GUARD_H_
#define GRAPHDB_SRC_STORAGE_STORAGE_GUARD_H_

#include <string>
#include <memory>

#include "leveldb/db.h"
#include "leveldb/filter_policy.h"

#include "storage/query/query_state.h"

namespace GraphDB {

enum StorageSection : uint8_t {
	Edge            = 0,
	NodeProperty    = 1,
	Identifier      = 2
};

enum EdgeDirection : uint8_t {
	Outbound = 0,
	Inbound  = 1
};

enum IdentifierType : uint8_t {
	EdgeType         = 0,
	NodePropertyType = 1,
	NodeId           = 2
};

class StorageGuard {
	public:
		explicit StorageGuard(const std::string&);
		~StorageGuard();

		leveldb::DB* getDb() const;
		QueryState::Ptr getQueryState() const;

	private:
		leveldb::DB* db_;
		leveldb::Options db_options_;
};

}

#endif  // GRAPHDB_SRC_STORAGE_STORAGE_GUARD_H_
