#include "query/logic/logic_or_subscription.h"

#include <algorithm>

namespace GraphDB {

bool LogicOrSubscription::check(uint32_t refId) {
	return std::any_of(this->subscriptions_.begin(),
	                   this->subscriptions_.end(),
	                   [&refId](const BasicSubscriptionPtr &s) -> bool {
	                       return s->check(refId);
	                   });
}

}
