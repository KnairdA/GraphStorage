#ifndef GRAPHDB_SRC_GRAPH_STORAGE_H
#define GRAPHDB_SRC_GRAPH_STORAGE_H

#include <string>
#include <memory>
#include <vector>

#include "storage/storage_guard.h"
#include "storage/storage_facade.h"

#include "storage/write/node_buffer.h"
#include "storage/write/maintenance_buffer.h"
#include "storage/query/edge_stream_distributor.h"

#include "query/logic_iterator.h"
#include "query/logic_subscription.h"

namespace GraphDB {

class GraphStorage {
	public:
		GraphStorage(const std::string&);

		QueryState::Ptr getQueryState() const;

		template <class Iter>
		typename Iter::Ptr getIterator(const QueryState*) const;

		template <class Subscription>
		LogicSubscription::Ptr getLogicSubscription(SubscriptionRecipient*);

		template <IdentifierType KeyType, typename ValueType>
		ValueType resolveIdentifier(std::string, PropertyValue&);

		void commitBuffer(WriteBuffer*);

	private:
		StorageGuard storage_;
		StorageFacade storage_facade_;
		EdgeStreamDistributor edge_stream_distributor_;

};

}

#endif  // GRAPHDB_SRC_GRAPH_STORAGE_H
