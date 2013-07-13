#ifndef GRAPHDB_SRC_QUERY_LOGIC_XOR_ITERATOR_H_
#define GRAPHDB_SRC_QUERY_LOGIC_XOR_ITERATOR_H_

#include <stack>

#include "query/logic_iterator.h"

namespace GraphDB {

class LogicXorIterator : public LogicIterator {
	public:
		using LogicIterator::LogicIterator;

	private:
		virtual bool iteratorsCheckCommon();
		virtual void resetInternals();

		std::stack<BasicIterator::Ptr> done_iterators_;
		uint32_t visited_id_ = 0;
};

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_XOR_ITERATOR_H_
