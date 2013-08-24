#include "storage/query/storage_cursor.h"
#include "exceptions.h"

#include "storage/buffer_utils.h"
#include "storage/id/identifier_id.h"

namespace GraphDB {

template <class Key>
StorageCursor<Key>::StorageCursor(std::unique_ptr<leveldb::Iterator> cur):
	cursor_(std::move(cur)),
	key_buffer_() {
	if ( this->cursor_->status().ok() && this->cursor_->Valid() ) {
		this->has_next_ = Key::fromBuffer(
			this->curr_key_,
			reinterpret_cast<const void*>(this->cursor_->key().data())
		);
	} else {
		throw storage_record_exception();
	}
}

template <class Key>
bool StorageCursor<Key>::jump(const Key& id) {
	Key::toBuffer(id, this->key_buffer_);

	this->cursor_->Seek(
		leveldb::Slice(reinterpret_cast<char*>(this->key_buffer_.data),
		               this->key_buffer_.size)
	);

	if ( this->cursor_->status().ok() && this->cursor_->Valid() ) {
		this->has_next_ = Key::fromBuffer(
			this->curr_key_,
			reinterpret_cast<const void*>(this->cursor_->key().data())
		);

		return this->curr_key_ == id;
	} else {
		throw storage_record_exception();
	}
}

template <class Key>
Key StorageCursor<Key>::getCurrent() {
	return this->curr_key_;
}

template <class Key>
Key StorageCursor<Key>::getNext() {
	this->step();

	return this->curr_key_;
}

template <class Key>
bool StorageCursor<Key>::hasNext() {
	return this->has_next_;
}

template <class Key>
void StorageCursor<Key>::getCurrentValue(PropertyValue& value) {
	value.record.ParseFromArray(
		reinterpret_cast<const void*>(this->cursor_->value().data()),
		this->cursor_->value().size()
	);
}

template <class Key>
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
