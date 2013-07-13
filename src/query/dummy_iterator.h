#ifndef GRAPHDB_SRC_QUERY_DUMMY_ITERATOR_H_
#define GRAPHDB_SRC_QUERY_DUMMY_ITERATOR_H_

#include "basic_iterator.h"
#include "storage/storage_facade.h"

namespace GraphDB {

class DummyIterator : public BasicIterator {
	public:
		DummyIterator(const StorageFacade*, const QueryState*) { };

		virtual uint32_t getCurrent();
		virtual uint32_t getNext();
		virtual bool hasNext();
		virtual bool jumpTo(uint32_t);

	private:
		void step();

		uint32_t curr_id_ = 0;

};

}

#endif  // GRAPHDB_SRC_QUERY_DUMMY_ITERATOR_H_
