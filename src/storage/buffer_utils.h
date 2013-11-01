#ifndef GRAPHDB_SRC_STORAGE_BUFFER_UTILS_H_
#define GRAPHDB_SRC_STORAGE_BUFFER_UTILS_H_

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <memory>

#include "exceptions.h"
#include "storage_guard.h"

namespace GraphDB {

template <class Key>
void writeNumber(void*, const Key&);

template <class Key>
Key readNumber(const void*);

void writeString(void*, const std::string&);
std::string readString(const void*);

struct NullBuffer {
	static const size_t Size = 0;
};

template <class Key>
struct BufferGuard {
	typedef typename std::unique_ptr<BufferGuard<Key>> Ptr;

	BufferGuard():
		data(std::malloc(Key::Size)),
		size(Key::Size) { }

	~BufferGuard() {
		std::free(data);
	}

	void resize(size_t newSize) {
		if ( newSize < Key::Size ) {
			throw buffer_size_exception();
		} else {
			data = std::realloc(data, newSize);
			size = newSize;
		}
	}

	void* data;
	size_t size; 
};

}

#endif  // GRAPHDB_SRC_STORAGE_BUFFER_UTILS_H_
