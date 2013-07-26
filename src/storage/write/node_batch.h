#ifndef GRAPHDB_SRC_WRITE_NODE_BATCH_H_
#define GRAPHDB_SRC_WRITE_NODE_BATCH_H_

#include "basic_iterator.h"
#include "storage/write/write_batch.h"

namespace GraphDB {

class NodeBatch : public WriteBatch {
	public:
		typedef std::unique_ptr<NodeBatch> Ptr;

		NodeBatch(BasicIterator* const);

		uint32_t getCurrent();

		void create();
		void discard();

		void connectTo(uint32_t, uint16_t);
		void disconnectFrom(uint32_t, uint16_t);

		void setProperty(uint16_t, const PropertyValue&);
		void removeProperty(uint16_t);

	private:
		BasicIterator* const iterator_;

};

}

#endif  // GRAPHDB_SRC_WRITE_NODE_BATCH_H_
