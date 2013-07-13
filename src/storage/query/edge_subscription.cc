#include "storage/query/edge_subscription.h"

namespace GraphDB {

EdgeSubscription::EdgeSubscription(EdgeStreamDistributor* distributor,
                                   StorageFacade* storage,
                                   SubscriptionRecipient* parent,
                                   uint32_t fromId,
                                   uint16_t typeId,
                                   EdgeDirection direction):
	parent_(parent),
	storage_(storage),
	distributor_(distributor),
	edge_(fromId, typeId, direction, 0) { }

void EdgeSubscription::pushNext(const EdgeStreamEvent& event) {
	if ( event.Type == INSERT || event.Type == UPDATE ) {
		this->parent_->pushNext(event.Edge.toId);
	}
}

bool EdgeSubscription::check(uint32_t toId) {
	EdgeId checkId(this->edge_.fromId,
	               this->edge_.typeId,
	               this->edge_.direction,
	               toId);

	return this->storage_->check<EdgeId>(checkId);
}

void EdgeSubscription::activate() {
	if ( !this->pattern_ ) {
		this->pattern_ = this->distributor_->getPattern(this);
		this->pattern_->setFromId(this->edge_.fromId);
		this->pattern_->setDirection(this->edge_.direction);
		this->pattern_->setTypeId(this->edge_.typeId);
	}
}

}
