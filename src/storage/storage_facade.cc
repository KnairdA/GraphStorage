#include "storage/storage_facade.h"
#include "exceptions.h"

#include "storage/buffer_utils.h"

namespace GraphDB {

StorageFacade::StorageFacade(StorageGuard& storage):
	db_(storage.getDb()) { }

template <class Key>
typename StorageCursor<Key>::Ptr
StorageFacade::getCursor(const Key& id, const QueryState* state) const {
	return typename StorageCursor<Key>::Ptr(
		new StorageCursor<Key>(
			this->getInternalCursor<Key>(id, state->getReadOptions())
		)
	);
}

void StorageFacade::commitBatch(leveldb::WriteBatch& buffer) {
	if ( !this->db_->Write(leveldb::WriteOptions(), &buffer).ok() ) {
		throw storage_transaction_exception();
	}
}

template <class Key>
bool StorageFacade::get(const Key& id, PropertyValue& target) const {
	BufferGuard<Key> keyBuffer;
	Key::toBuffer(id, keyBuffer);

	leveldb::Slice key(reinterpret_cast<char*>(keyBuffer.data),
	                   keyBuffer.size);
	std::string value;

	if ( !this->db_->Get(leveldb::ReadOptions(), key, &value).IsNotFound() ) {
		target.record.ParseFromArray(
			reinterpret_cast<const void*>(value.data()), value.size()
		);

		return true;
	} else {
		return false;
	}
}

template <class Key>
bool StorageFacade::check(const Key& id) const {
	BufferGuard<Key> keyBuffer;
	Key::toBuffer(id, keyBuffer);

	leveldb::Slice key(reinterpret_cast<char*>(keyBuffer.data),
	                   keyBuffer.size);
	std::string value;

	return !this->db_->Get(leveldb::ReadOptions(), key, &value).IsNotFound();
}

template <class Key> typename
std::unique_ptr<leveldb::Iterator> StorageFacade::getInternalCursor(
	const Key& id,
	const leveldb::ReadOptions& options) const {
	BufferGuard<Key> keyBuffer;
	Key::toBuffer(id, keyBuffer);

	std::unique_ptr<leveldb::Iterator> cursor(this->db_->NewIterator(options));

	cursor->Seek(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer.data),
		               keyBuffer.size)
	);

	if ( cursor->status().ok() && cursor->Valid() ) {
		return cursor;
	} else {
		throw storage_record_exception();
	}
}

}

#include "storage/storage_facade.tmpl"
