#ifndef GRAPHDB_SRC_GRAPH_STORAGE_H
#define GRAPHDB_SRC_GRAPH_STORAGE_H

#include <string>
#include <memory>
#include <vector>

#include "storage/storage_guard.h"
#include "storage/storage_facade.h"

#include "storage/write/node_batch.h"
#include "storage/query/edge_stream_distributor.h"

#include "query/logic_iterator.h"
#include "query/logic_subscription.h"

namespace GraphDB {

class GraphStorage {
	public:
		explicit GraphStorage(const std::string&);
		GraphStorage(const std::string&, leveldb::Options);

		QueryState::Ptr getQueryState() const;

		template <class Iter>
		typename Iter::Ptr getIterator(const QueryState*) const;

		template <class Subscription>
		typename Subscription::Ptr getSubscription(SubscriptionRecipient*);

		template <IdentifierType KeyType, typename ValueType>
		ValueType resolveIdentifier(std::string, PropertyValue&);

		void commitBatch(WriteBatch*);

	private:
		StorageGuard storage_;
		StorageFacade storage_facade_;
		EdgeStreamDistributor edge_stream_distributor_;

};

}

#endif  // GRAPHDB_SRC_GRAPH_STORAGE_H
