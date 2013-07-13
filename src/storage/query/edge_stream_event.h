#ifndef GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_EVENT_H_
#define GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_EVENT_H_

#include "storage/id/edge_id.h"

namespace GraphDB {

enum EdgeStreamEventType {
	INSERT,
	UPDATE,
	REMOVE
};

struct EdgeStreamEvent {
	EdgeStreamEvent(EdgeStreamEventType type, EdgeId id):
		Type(type), Edge(id) {};

	const EdgeStreamEventType Type;
	const EdgeId Edge;
};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_EVENT_H_
