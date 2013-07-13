#ifndef GRAPHDB_SRC_BASIC_SUBSCRIPTION_H_
#define GRAPHDB_SRC_BASIC_SUBSCRIPTION_H_

#include "storage/query/edge_stream_pattern.h"

namespace GraphDB {

class SubscriptionRecipient {
	public:
		virtual void pushNext(uint32_t) = 0;
};

class BasicSubscription : public SubscriptionRecipient {
	public:
		virtual ~BasicSubscription() {};

		virtual void pushNext(uint32_t) = 0;
		virtual bool check(uint32_t)    = 0;
		virtual void activate()         = 0;
};

}

#endif  // GRAPHDB_SRC_BASIC_SUBSCRIPTION_H_
