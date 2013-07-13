#ifndef GRAPHDB_SRC_BASIC_ITERATOR_H_
#define GRAPHDB_SRC_BASIC_ITERATOR_H_

#include <cstdint>
#include <memory>

namespace GraphDB {

class BasicIterator {
	public:
		typedef std::unique_ptr<BasicIterator> Ptr;

		virtual ~BasicIterator() {};

		virtual uint32_t getCurrent()    = 0;
		virtual uint32_t getNext()       = 0;
		virtual bool hasNext()           = 0;
		virtual bool jumpTo(uint32_t)    = 0;
};

}

#endif  // GRAPHDB_SRC_BASIC_ITERATOR_H_
