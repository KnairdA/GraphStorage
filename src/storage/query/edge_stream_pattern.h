#ifndef GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_PATTERN_H_
#define GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_PATTERN_H_

#include "storage/id/edge_id.h"
#include "storage/query/edge_stream_event.h"

namespace GraphDB {

class EdgeStreamRecipient {
	public:
		virtual void pushNext(const EdgeStreamEvent&) = 0;
};

class EdgeStreamPattern {
	public:
		EdgeStreamPattern(EdgeStreamRecipient*);

		bool evaluate(const EdgeStreamEvent&);

		void setFromId(uint32_t);
		void setTypeId(uint16_t);
		void setDirection(EdgeDirection);
		void setToId(uint32_t);

	private:
		bool isMatchingPattern(const EdgeStreamEvent&);

		EdgeStreamRecipient* recipient_;

		EdgeId edge_;
		bool from_id_set_   = false;
		bool type_id_set_   = false;
		bool direction_set_ = false;
		bool to_id_set_     = false;
};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_PATTERN_H_
