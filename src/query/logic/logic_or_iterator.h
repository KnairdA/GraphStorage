#ifndef GRAPHDB_SRC_QUERY_LOGIC_OR_ITERATOR_H_
#define GRAPHDB_SRC_QUERY_LOGIC_OR_ITERATOR_H_

#include <vector>

#include "query/logic_iterator.h"

namespace GraphDB {

class LogicOrIterator : public LogicIterator {
	public:
		using LogicIterator::LogicIterator;

	private:
		virtual bool iteratorsCheckCommon();
		virtual void resetBeforeJump(uint32_t);
 
		std::vector<BasicIterator::Ptr> done_iterators_;
};

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_OR_ITERATOR_H_
