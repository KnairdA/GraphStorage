#ifndef GRAPHDB_SRC_QUERY_LOGIC_OR_ITERATOR_H_
#define GRAPHDB_SRC_QUERY_LOGIC_OR_ITERATOR_H_

#include <stack>

#include "query/logic_iterator.h"

namespace GraphDB {

class LogicOrIterator : public LogicIterator {
	public:
		using LogicIterator::LogicIterator;

	private:
		virtual bool iteratorsCheckCommon();
		virtual void resetInternals();
 
		std::stack<BasicIterator::Ptr> done_iterators_;
};

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_OR_ITERATOR_H_
