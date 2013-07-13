#include "storage/query/query_state.h"

#include "storage/storage_guard.h"

namespace GraphDB {

QueryState::QueryState(const StorageGuard& storage):
	db_(storage.getDb()) {
	this->state_ = this->db_->GetSnapshot();
}

QueryState::~QueryState() {
	this->db_->ReleaseSnapshot(this->state_);
}

const leveldb::Snapshot* QueryState::getState() const {
	return this->state_;
}

leveldb::ReadOptions QueryState::getReadOptions() const {
	leveldb::ReadOptions options;
	options.snapshot = this->state_;

	return options;
}

}
