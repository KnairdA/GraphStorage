#include "query/logic/logic_or_iterator.h"

#include <algorithm>
#include <vector>

namespace GraphDB {

bool LogicOrIterator::iteratorsCheckCommon() {
	auto minIter = this->iteratorsGetMin();

	while ( !(*minIter)->hasNext() && this->iterators_.size() > 1 ) {
		this->done_iterators_.push(std::move(*minIter));
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

void LogicOrIterator::resetInternals() {
	while ( !this->done_iterators_.empty() ) {
		this->iterators_.emplace_back(
			std::move(this->done_iterators_.top())
		);
		this->done_iterators_.pop();
	}
}

}
