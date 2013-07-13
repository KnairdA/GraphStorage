#include "query/logic/logic_xor_iterator.h"

#include <algorithm>
#include <vector>

namespace GraphDB {

bool LogicXorIterator::iteratorsCheckCommon() {
	auto minIter = this->iteratorsGetMin();

	while ( !(*minIter)->hasNext() && this->iterators_.size() > 1 ) {
		this->done_iterators_.push(std::move(*minIter));
		this->iterators_.erase(minIter);

		minIter = this->iteratorsGetMin();
	}

	uint32_t refId = (*minIter)->getCurrent();
	uint32_t oldVisitedId = this->visited_id_;

	auto checkFunc = [&refId](const BasicIterator::Ptr &i) -> bool {
		return i->getCurrent() == refId;
	};

	uint32_t equalToRefId = std::count_if(this->iterators_.begin(),
	                                      this->iterators_.end(),
	                                      checkFunc);
	this->visited_id_ = refId;

	if ( equalToRefId == 1 ) {
		if ( oldVisitedId >= refId ) {
			return false;
		} else {
			this->curr_common_id_ = refId;
			return true;
		}
	} else {
		return false;
	}
}

void LogicXorIterator::resetInternals() {
	while ( !this->done_iterators_.empty() ) {
		this->iterators_.emplace_back(
			std::move(this->done_iterators_.top())
		);
		this->done_iterators_.pop();
	}

	this->visited_id_ = 0;
}

}
