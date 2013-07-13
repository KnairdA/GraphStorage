#include "storage/query/storage_cursor.h"
#include "exceptions.h"

#include "storage/buffer_utils.h"

namespace GraphDB {

template <typename Key>
StorageCursor<Key>::StorageCursor(std::unique_ptr<leveldb::Iterator> cur):
	cursor_(std::move(cur)) {
	if ( this->cursor_->status().ok() && this->cursor_->Valid() ) {
		this->has_next_ = Key::fromBuffer(
			this->curr_key_,
			reinterpret_cast<const void*>(this->cursor_->key().data())
		);
	} else {
		throw storage_record_exception();
	}
}

template <typename Key>
bool StorageCursor<Key>::jump(const Key& id) {
	if ( this->jumpApproximately(id) ) {
		return this->curr_key_ == id;
	} else {
		throw storage_record_exception();
	}
}

template <typename Key>
Key StorageCursor<Key>::getCurrent() {
	return this->curr_key_;
}

template <typename Key>
Key StorageCursor<Key>::getNext() {
	this->step();

	return this->curr_key_;
}

template <typename Key>
bool StorageCursor<Key>::hasNext() {
	return this->has_next_;
}

template <typename Key>
void StorageCursor<Key>::getCurrentValue(PropertyValue& value) {
	value.record.ParseFromArray(
		reinterpret_cast<const void*>(this->cursor_->value().data()),
		this->cursor_->value().size()
	);
}

template <typename Key>
bool StorageCursor<Key>::jumpApproximately(const Key& id) {
	BufferGuard::Ptr keyBuffer(Key::toBuffer(id));

	this->cursor_->Seek(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer->data),
		               keyBuffer->size)
	);

	if ( this->cursor_->status().ok() && this->cursor_->Valid() ) {
		this->has_next_ = Key::fromBuffer(
			this->curr_key_,
			reinterpret_cast<const void*>(this->cursor_->key().data())
		);

		return true;
	} else {
		return false;
	}
}

template <typename Key>
void StorageCursor<Key>::step() {
	this->cursor_->Next();

	if ( this->cursor_->status().ok() && this->cursor_->Valid() ) {
		this->has_next_ = Key::fromBuffer(
			this->curr_key_,
			reinterpret_cast<const void*>(this->cursor_->key().data())
		);
	} else {
		if ( this->has_next_ ) {
			this->has_next_  = false;
		} else {
			throw storage_record_exception();
		}
	}
}

}

#include "storage/query/storage_cursor.tmpl"
