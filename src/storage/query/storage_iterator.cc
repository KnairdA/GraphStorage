#include "storage/query/storage_iterator.h"
#include "exceptions.h"

namespace GraphDB {

template <class Key>
StorageIterator<Key>::StorageIterator(const StorageFacade* storage,
                                      const QueryState* state,
                                      const Key& pos):
	position_(pos),
	cursor_(storage->getCursor<Key>(position_, state)),
	has_next_(cursor_->hasNext()) {
	this->position_.nodeId = this->cursor_->getCurrent().nodeId;
}

template <class Key>
uint32_t StorageIterator<Key>::getCurrent() {
	return this->position_.nodeId;
}

template <class Key>
uint32_t StorageIterator<Key>::getNext() {
	this->step();

	return this->position_.nodeId;
}

template <class Key>
bool StorageIterator<Key>::hasNext() {
	return this->has_next_;
}

template <class Key>
bool StorageIterator<Key>::jumpTo(uint32_t id) {
	uint32_t oldId         = this->position_.nodeId;
	this->position_.nodeId = id;

	if ( this->cursor_->jump(this->position_) ) {
		this->has_next_  = this->cursor_->hasNext();
	} else {
		if ( Key::equalArea(this->cursor_->getCurrent(),
		                    this->position_) ) {
			this->has_next_  = this->cursor_->hasNext();
			this->position_.nodeId = this->cursor_->getCurrent().nodeId;
		} else {
			this->has_next_  = false;
			this->position_.nodeId = oldId;
		}
	}

	return this->position_.nodeId == id;
}

template <class Key>
void StorageIterator<Key>::getCurrentValue(PropertyValue& value) {
	this->cursor_->getCurrentValue(value);
}

template <class Key>
void StorageIterator<Key>::step() {
	if ( this->has_next_ ) {
		if ( this->cursor_->hasNext() ) {
			if ( Key::equalArea(this->cursor_->getNext(),
			                    this->position_) ) {
				this->has_next_        = this->cursor_->hasNext();
				this->position_.nodeId = this->cursor_->getCurrent().nodeId;
			} else {
				this->has_next_ = false;
			}
		} else {
			if ( this->has_next_ ) {
				this->has_next_ = false;
			} else {
				throw internal_iterator_exception();
			}
		}
	} else {
		throw internal_iterator_exception();
	}
}

}

#include "storage/query/storage_iterator.tmpl"
