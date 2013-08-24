#include "query/logic/logic_or_iterator.h"

#include <algorithm>

namespace GraphDB {

bool LogicOrIterator::iteratorsCheckCommon() {
	auto minIter = this->iteratorsGetMin();

	while ( !(*minIter)->hasNext() && this->iterators_.size() > 1 ) {
		this->done_iterators_.emplace_back(std::move(*minIter));
		this->iterators_.erase(minIter);

		minIter = this->iteratorsGetMin();
	}

	if ( this->curr_common_id_ == (*minIter)->getCurrent() ) {
		return false;
	} else {
		this->curr_common_id_ = (*minIter)->getCurrent();
		return true;
	}
}

void LogicOrIterator::resetBeforeJump(uint32_t id) {
	for ( auto iter = this->done_iterators_.begin();
	      iter != this->done_iterators_.end();
	      ++iter ) {
		if ( (*iter)->getCurrent() > id ) {
			this->iterators_.emplace_back(
				std::move(*iter)
			);
			this->done_iterators_.erase(iter);
		}
	}
}

}
