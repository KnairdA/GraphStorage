#include "query/dummy_iterator.h"
#include "exceptions.h"

namespace GraphDB {

uint32_t DummyIterator::getCurrent() {
	return this->curr_id_;
}

uint32_t DummyIterator::getNext() {
	this->step();

	return this->curr_id_;
}

bool DummyIterator::hasNext() {
	return this->curr_id_ < UINT32_MAX;
}

bool DummyIterator::jumpTo(uint32_t id) {
	this->curr_id_ = id;

	return true;
}

void DummyIterator::step() {
	if ( this->hasNext() ) {
		this->curr_id_++;
	} else {
		throw internal_iterator_exception();
	}
}

}
