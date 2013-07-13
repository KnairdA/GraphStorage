#ifndef GRAPHDB_SRC_WRITE_NODE_BUFFER_H_
#define GRAPHDB_SRC_WRITE_NODE_BUFFER_H_

#include "basic_iterator.h"
#include "storage/write/write_buffer.h"

namespace GraphDB {

class NodeBuffer : public WriteBuffer {
	public:
		typedef std::unique_ptr<NodeBuffer> Ptr;

		NodeBuffer(BasicIterator* const);

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

#endif  // GRAPHDB_SRC_WRITE_NODE_BUFFER_H_
