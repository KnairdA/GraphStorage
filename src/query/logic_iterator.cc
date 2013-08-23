#include "query/logic_iterator.h"

#include <algorithm>

namespace GraphDB {

LogicIterator::LogicIterator(const StorageFacade* storage,
                             const QueryState* state):
	storage_(storage),
	state_(state) { }

uint32_t LogicIterator::getCurrent() {
	!this->is_initialized_ ? this->initialize() : void();

	return this->curr_common_id_;
}

uint32_t LogicIterator::getNext() {
	!this->is_initialized_ ? this->initialize() : void();

	this->step();
	return this->curr_common_id_;
}

bool LogicIterator::hasNext() {
	!this->is_initialized_ ? this->initialize() : void();

	return this->has_next_;
}

bool LogicIterator::jumpTo(uint32_t id) {
	this->curr_common_id_ = 0;
	this->resetInternals();

	std::for_each(this->iterators_.begin(),
	              this->iterators_.end(),
	              [&id](const BasicIterator::Ptr& i) {
	                  i->jumpTo(id); 
	              });

	if ( this->is_initialized_ ) {
		this->has_next_ = this->iteratorsHaveNext();

		if ( !this->iteratorsCheckCommon() ) {
			if ( this->hasNext() ) {
				this->getNext();
			}
		}
	} else {
		this->initialize();
	}

	return this->curr_common_id_ == id;
}

std::vector<BasicIterator::Ptr>::iterator LogicIterator::iteratorsGetMin() {
	auto checkFunc = [](const BasicIterator::Ptr& i1,
	                    const BasicIterator::Ptr& i2) -> bool {
		return i1->getCurrent() < i2->getCurrent();
	};

	return std::min_element(this->iterators_.begin(),
	                        this->iterators_.end(),
	                        checkFunc);
}

void LogicIterator::initialize() {
	if ( !this->iterators_.empty() ) {
		if ( !this->iteratorsCheckCommon() ) {
			this->step();

			if ( !this->has_next_ ) {
				throw internal_iterator_exception();
			}
		}

		this->is_initialized_ = true;
	} else {
		throw internal_iterator_exception();
	}
}

void LogicIterator::step() {
	if ( this->has_next_ ) {
		if ( this->iteratorsHaveNext() ) {
			uint32_t oldCommonId = this->curr_common_id_;

			this->iteratorsGetNext();

			if ( this->curr_common_id_ == oldCommonId ) {
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

bool LogicIterator::iteratorsHaveNext() {
	return std::any_of(this->iterators_.begin(),
	                   this->iterators_.end(),
	                   [](const BasicIterator::Ptr& i) -> bool {
	                       return i->hasNext();
	                   });
}

void LogicIterator::iteratorsGetNext() {
	do {
		auto minIter = this->iteratorsGetMin();

		if ( (*minIter)->hasNext() ) {
			(*minIter)->getNext();
		} else {
			this->has_next_ = false;
		}
	}
	while ( !this->iteratorsCheckCommon() &&
	        this->iteratorsHaveNext()     &&
	        this->has_next_ );
}

}
