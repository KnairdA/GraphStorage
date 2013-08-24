#ifndef GRAPHDB_SRC_QUERY_LOGIC_AND_ITERATOR_H_
#define GRAPHDB_SRC_QUERY_LOGIC_AND_ITERATOR_H_

#include <vector>

#include "query/logic_iterator.h"

namespace GraphDB {

class LogicAndIterator : public LogicIterator {
	public:
		using LogicIterator::LogicIterator;

	private:
		virtual bool iteratorsCheckCommon();
		std::vector<BasicIterator::Ptr>::iterator iteratorsGetMax();

		uint8_t iterators_move_count_ = 0;
};

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_AND_ITERATOR_H_
