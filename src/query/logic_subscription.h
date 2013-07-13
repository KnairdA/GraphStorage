#ifndef GRAPHDB_SRC_QUERY_LOGIC_SUBSCRIPTION_H_
#define GRAPHDB_SRC_QUERY_LOGIC_SUBSCRIPTION_H_

#include <memory>
#include <vector>

#include "basic_subscription.h"
#include "storage/storage_facade.h"
#include "storage/query/edge_stream_distributor.h"

namespace GraphDB {

typedef std::unique_ptr<BasicSubscription> BasicSubscriptionPtr;

class LogicSubscription : public BasicSubscription {
	public:
		typedef std::unique_ptr<LogicSubscription> Ptr;

		LogicSubscription(EdgeStreamDistributor*,
		                  StorageFacade*,
		                  SubscriptionRecipient*);
		virtual ~LogicSubscription() { }

		virtual void pushNext(uint32_t);
		virtual void activate();

		template <typename Subscription, typename... Args>
		Subscription* getSubscription(Args&&... args);

		virtual bool check(uint32_t) = 0;

	protected:
		std::vector<BasicSubscriptionPtr> subscriptions_;

	private:
		EdgeStreamDistributor* distributor_;
		StorageFacade* storage_;
		SubscriptionRecipient* parent_;

};

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_SUBSCRIPTION_H_
