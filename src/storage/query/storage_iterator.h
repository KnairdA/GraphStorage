#ifndef GRAPHDB_SRC_STORAGE_QUERY_STORAGE_ITERATOR_H_
#define GRAPHDB_SRC_STORAGE_QUERY_STORAGE_ITERATOR_H_

#include "basic_iterator.h"
#include "storage/storage_facade.h"
#include "storage/id/edge_id.h"
#include "storage/id/node_property_id.h"

namespace GraphDB {

template <class Key>
class StorageIterator : public BasicIterator {
	public:
		StorageIterator(const StorageFacade*,
		                const QueryState*,
		                const Key&);

		virtual uint32_t getCurrent();
		virtual uint32_t getNext();
		virtual bool hasNext();
		virtual bool jumpTo(uint32_t);

		void getCurrentValue(PropertyValue&);

	private:
		void step();

		Key position_;
		typename StorageCursor<Key>::Ptr cursor_;
		bool has_next_;

};

typedef StorageIterator<EdgeId> EdgeIterator;
typedef StorageIterator<NodePropertyId> PropertyIterator;

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_STORAGE_ITERATOR_H_
