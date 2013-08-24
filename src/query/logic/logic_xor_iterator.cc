#include "query/logic/logic_xor_iterator.h"

#include <algorithm>

namespace GraphDB {

bool LogicXorIterator::iteratorsCheckCommon() {
	auto minIter = this->iteratorsGetMin();

	while ( !(*minIter)->hasNext() && this->iterators_.size() > 1 ) {
		this->done_iterators_.emplace_back(std::move(*minIter));
		this->iterators_.erase(minIter);

		minIter = this->iteratorsGetMin();
	}

	uint32_t refId        = (*minIter)->getCurrent();
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

void LogicXorIterator::resetBeforeJump(uint32_t id) {
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

	this->visited_id_ = 0;
}

}
