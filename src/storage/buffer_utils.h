#ifndef GRAPHDB_SRC_STORAGE_BUFFER_UTILS_H_
#define GRAPHDB_SRC_STORAGE_BUFFER_UTILS_H_

#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <memory>

#include "storage_guard.h"

namespace GraphDB {

struct BufferGuard {
	typedef std::unique_ptr<BufferGuard> Ptr;

	BufferGuard(size_t);
	~BufferGuard();

	void* const data;
	const size_t size; 
};

template <typename Key>
void writeNumber(void*, Key);

template <typename Key>
Key readNumber(const void*);

void writeString(void*, std::string);
std::string readString(const void*);

}

#endif  // GRAPHDB_SRC_STORAGE_BUFFER_UTILS_H_
