#include "query/logic/logic_and_iterator.h"

#include <algorithm>

namespace GraphDB {

bool LogicAndIterator::iteratorsCheckCommon() {
	this->iterators_move_count_++;

	uint32_t refId = this->iterators_.front()->getCurrent();

	auto checkFunc = [&refId](const BasicIterator::Ptr &i) -> bool {
		return i->getCurrent() == refId;
	};

	bool equalToRefId = std::all_of(this->iterators_.begin(),
	                                this->iterators_.end(),
	                                checkFunc);

	if ( equalToRefId ) {
		this->curr_common_id_       = refId;
		this->iterators_move_count_ = 0;

		return true;
	} else {
		if ( this->iterators_move_count_ > 2 ) {
			uint32_t maxId = (*this->iteratorsGetMax())->getCurrent();

			std::for_each(this->iterators_.begin(),
			              this->iterators_.end(),
			              [&maxId](const BasicIterator::Ptr& i) {
			                  if ( i->getCurrent() < maxId ) {
			                      i->jumpTo(maxId); 
			                  }
			              });

			this->iterators_move_count_ = 0;

			return this->iteratorsCheckCommon();
		} else {
			return false;
		}
	}
}

std::vector<BasicIterator::Ptr>::iterator LogicAndIterator::iteratorsGetMax() {
	auto checkFunc = [](const BasicIterator::Ptr &i1,
	                    const BasicIterator::Ptr &i2) -> bool {
		return i1->getCurrent() < i2->getCurrent();
	};

	return std::max_element(this->iterators_.begin(),
	                        this->iterators_.end(),
	                        checkFunc);
}

}
