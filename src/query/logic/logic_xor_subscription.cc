#include "query/logic/logic_xor_subscription.h"

#include <algorithm>

namespace GraphDB {

LogicXorSubscription::LogicXorSubscription(EdgeStreamDistributor* distributor,
                                           StorageFacade* edgeDb,
                                           SubscriptionRecipient* parent):
	LogicSubscription(distributor, edgeDb, parent) { }

bool LogicXorSubscription::check(uint32_t refId) {
	uint32_t equalToRefId = std::count_if(this->subscriptions_.begin(),
	                                      this->subscriptions_.end(),
	                                      [&refId](const BasicSubscriptionPtr &s) -> bool {
	                                          return s->check(refId);
	                                      });
	return equalToRefId == 1;
}

}
