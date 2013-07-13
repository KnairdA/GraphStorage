#ifndef GRAPHDB_SRC_STORAGE_QUERY_EDGE_ITERATOR_H_
#define GRAPHDB_SRC_STORAGE_QUERY_EDGE_ITERATOR_H_

#include "basic_iterator.h"
#include "storage/id/edge_id.h"
#include "storage/storage_facade.h"

namespace GraphDB {

class EdgeIterator : public BasicIterator {
	public:
		typedef EdgeId CursorKey;

		EdgeIterator(const StorageFacade*,
		             const QueryState*,
		             uint32_t,
		             uint16_t,
		             EdgeDirection);

		virtual uint32_t getCurrent();
		virtual uint32_t getNext();
		virtual bool hasNext();
		virtual bool jumpTo(uint32_t);

	private:
		void step();

		CursorKey edge_;
		StorageCursor<CursorKey>::Ptr cursor_;
		bool has_next_;

};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_EDGE_ITERATOR_H_
