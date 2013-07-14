#ifndef GRAPHDB_SRC_STORAGE_QUERY_EDGE_SUBSCRIPTION_H_
#define GRAPHDB_SRC_STORAGE_QUERY_EDGE_SUBSCRIPTION_H_

#include <memory>

#include "basic_subscription.h"
#include "storage/id/edge_id.h"
#include "storage/storage_facade.h"
#include "storage/query/edge_stream_distributor.h"

namespace GraphDB {

class EdgeSubscription : public BasicSubscription,
                         public EdgeStreamRecipient {
	public:
		EdgeSubscription(EdgeStreamDistributor*,
		                 const StorageFacade*,
		                 SubscriptionRecipient*,
		                 uint32_t,
		                 uint16_t,
		                 EdgeDirection);

		virtual void pushNext(uint32_t) { };
		virtual void pushNext(const EdgeStreamEvent&);
		virtual bool check(uint32_t);

		virtual void activate();

	private:
		SubscriptionRecipient* parent_;
		const StorageFacade* storage_;
		EdgeStreamDistributor* distributor_;
		EdgeId edge_;

		std::shared_ptr<EdgeStreamPattern> pattern_;
};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_EDGE_SUBSCRIPTION_H_
