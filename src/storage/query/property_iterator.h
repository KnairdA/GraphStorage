#ifndef GRAPHDB_SRC_STORAGE_QUERY_PROPERTY_ITERATOR_H_
#define GRAPHDB_SRC_STORAGE_QUERY_PROPERTY_ITERATOR_H_

#include "basic_iterator.h"
#include "storage/id/node_property_id.h"
#include "storage/storage_facade.h"

namespace GraphDB {

class PropertyIterator : public BasicIterator {
	public:
		typedef NodePropertyId CursorKey;

		PropertyIterator(const StorageFacade*,
		                 const QueryState*,
		                 uint16_t);

		virtual uint32_t getCurrent();
		virtual uint32_t getNext();
		virtual bool hasNext();
		virtual bool jumpTo(uint32_t);

		void getCurrentValue(PropertyValue&);

	private:
		void step();

		CursorKey property_;
		StorageCursor<CursorKey>::Ptr cursor_;
		bool has_next_;

};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_PROPERTY_ITERATOR_H_
