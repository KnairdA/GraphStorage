#include "query/logic_subscription.h"

#include <algorithm>

namespace GraphDB {

LogicSubscription::LogicSubscription(EdgeStreamDistributor* distributor,
                                     StorageFacade* edgeDb,
                                     SubscriptionRecipient* parent):
	distributor_(distributor),
	storage_(edgeDb),
	parent_(parent) { }

void LogicSubscription::pushNext(uint32_t id) {
	if ( this->check(id) ) {
		this->parent_->pushNext(id);
	}
}

void LogicSubscription::activate() {
	std::for_each(this->subscriptions_.begin(),
	              this->subscriptions_.end(),
	              [](BasicSubscriptionPtr &s) {
	                  s->activate();
	              });
}

template <typename Subscription, typename... Args>
Subscription* LogicSubscription::getSubscription(Args&&... args) {
	this->subscriptions_.emplace_back(
		new Subscription(this->distributor_,
		                 this->storage_,
		                 this,
		                 std::forward<Args>(args)...)
	);

	return static_cast<Subscription*>(this->subscriptions_.back().get());
}

}

#include "query/logic_subscription.tmpl"
