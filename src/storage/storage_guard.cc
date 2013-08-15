#include "storage/storage_guard.h"
#include "exceptions.h"

#include "leveldb/cache.h"

namespace GraphDB {

StorageGuard::StorageGuard(const std::string& path) {
	this->db_options_.create_if_missing = true;
	this->db_options_.block_cache       = leveldb::NewLRUCache(104857600);
	this->db_options_.filter_policy     = leveldb::NewBloomFilterPolicy(64);

	leveldb::Status status = leveldb::DB::Open(this->db_options_,
	                                           path,
	                                           &this->db_);

	if ( !status.ok() ) {
		throw storage_exception();
	}
}

StorageGuard::StorageGuard(const std::string& path, leveldb::Options options):
	db_options_(options) {
	leveldb::Status status = leveldb::DB::Open(this->db_options_,
	                                           path,
	                                           &this->db_);

	if ( !status.ok() ) {
		throw storage_exception();
	}
}

StorageGuard::~StorageGuard() {
	delete this->db_;
	delete this->db_options_.block_cache;
	delete this->db_options_.filter_policy;
}

leveldb::DB* StorageGuard::getDb() const {
	return this->db_;
}

}
