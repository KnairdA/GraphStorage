#include "query/logic/logic_and_subscription.h"

#include <algorithm>

namespace GraphDB {

LogicAndSubscription::LogicAndSubscription(EdgeStreamDistributor* distributor,
                                           StorageFacade* edgeDb,
                                           SubscriptionRecipient* parent):
	LogicSubscription(distributor, edgeDb, parent) { }

bool LogicAndSubscription::check(uint32_t refId) {
	return std::all_of(this->subscriptions_.begin(),
	                   this->subscriptions_.end(),
	                   [&refId](const BasicSubscriptionPtr &s) -> bool {
	                       return s->check(refId);
	                   });
}

}
