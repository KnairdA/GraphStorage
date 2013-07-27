#include "storage/query/edge_iterator.h"
#include "exceptions.h"

namespace GraphDB {

EdgeIterator::EdgeIterator(const StorageFacade* storage,
                           const QueryState* state,
                           uint32_t fromId,
                           uint16_t typeId,
                           EdgeDirection direction):
	edge_(fromId, typeId, direction, 0),
	cursor_(storage->getCursor<CursorKey>(edge_, state)),
	has_next_(cursor_->hasNext()) {
	this->edge_.toId = this->cursor_->getCurrent().toId;
}

uint32_t EdgeIterator::getCurrent() {
	return this->edge_.toId;
}

uint32_t EdgeIterator::getNext() {
	this->step();

	return this->edge_.toId;
}

bool EdgeIterator::hasNext() {
	return this->has_next_;
}

bool EdgeIterator::jumpTo(uint32_t id) {
	uint32_t oldId   = this->edge_.toId;
	this->edge_.toId = id;

	if ( this->cursor_->jump(this->edge_) ) {
		this->has_next_  = this->cursor_->hasNext();
		this->edge_.toId = this->cursor_->getCurrent().toId;
	} else {
		CursorKey edge(this->cursor_->getCurrent());

		if ( edge.fromId    == this->edge_.fromId &&
		     edge.typeId    == this->edge_.typeId &&
		     edge.direction == this->edge_.direction ) {
			this->has_next_  = this->cursor_->hasNext();
			this->edge_.toId = this->cursor_->getCurrent().toId;
		} else {
			this->has_next_  = false;
			this->edge_.toId = oldId;
		}
	}

	return this->edge_.toId == id;
}

void EdgeIterator::step() {
	if ( this->has_next_ ) {
		if ( this->cursor_->hasNext() ) {
			CursorKey edge  = this->cursor_->getNext();
			this->has_next_ = this->cursor_->hasNext();

			if ( edge.fromId    == this->edge_.fromId &&
			     edge.typeId    == this->edge_.typeId &&
			     edge.direction == this->edge_.direction ) {
				this->edge_.toId = edge.toId;
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
