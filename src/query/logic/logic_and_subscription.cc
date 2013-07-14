#include "query/logic/logic_and_subscription.h"

#include <algorithm>

namespace GraphDB {

bool LogicAndSubscription::check(uint32_t refId) {
	return std::all_of(this->subscriptions_.begin(),
	                   this->subscriptions_.end(),
	                   [&refId](const BasicSubscriptionPtr &s) -> bool {
	                       return s->check(refId);
	                   });
}

}
