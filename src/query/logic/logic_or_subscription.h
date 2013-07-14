#ifndef GRAPHDB_SRC_QUERY_LOGIC_LOGIC_OR_SUBSCRIPTION_H_
#define GRAPHDB_SRC_QUERY_LOGIC_LOGIC_OR_SUBSCRIPTION_H_

#include "query/logic_subscription.h"

namespace GraphDB {

class LogicOrSubscription : public LogicSubscription {
	public:
		using LogicSubscription::LogicSubscription;

		virtual bool check(uint32_t);
};

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_LOGIC_OR_SUBSCRIPTION_H_
