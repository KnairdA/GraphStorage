#include "storage/query/property_iterator.h"
#include "exceptions.h"

namespace GraphDB {

PropertyIterator::PropertyIterator(const StorageFacade* storage,
                                   const QueryState* state,
                                   uint16_t propertyId):
	property_(0, propertyId),
	cursor_(storage->getCursor<CursorKey>(property_, state)),
	has_next_(cursor_->hasNext()) {
	this->property_.nodeId = this->cursor_->getCurrent().nodeId;
}

uint32_t PropertyIterator::getCurrent() {
	return this->property_.nodeId;
}

uint32_t PropertyIterator::getNext() {
	this->step();

	return this->property_.nodeId;
}

bool PropertyIterator::hasNext() {
	return this->has_next_;
}

bool PropertyIterator::jumpTo(uint32_t id) {
	uint32_t oldId = this->property_.nodeId;
	this->property_.nodeId = id;

	if ( this->cursor_->jump(this->property_) ) {
		this->has_next_        = this->cursor_->hasNext();
		this->property_.nodeId = this->cursor_->getCurrent().nodeId;
	} else {
		CursorKey property(this->cursor_->getCurrent());

		if ( property.propertyId == this->property_.propertyId ) {
			this->has_next_  = this->cursor_->hasNext();
			this->property_.nodeId = this->cursor_->getCurrent().nodeId;
		} else {
			this->has_next_        = false;
			this->property_.nodeId = oldId;
		}
	}

	return this->property_.nodeId == id;
}

void PropertyIterator::getCurrentValue(PropertyValue& value) {
	this->cursor_->getCurrentValue(value);
}

void PropertyIterator::step() {
	if ( this->has_next_ ) {
		if ( this->cursor_->hasNext() ) {
			CursorKey property = this->cursor_->getNext();
			this->has_next_    = this->cursor_->hasNext();

			if ( property.propertyId == this->property_.propertyId ) {
				this->property_.nodeId = property.nodeId;
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
