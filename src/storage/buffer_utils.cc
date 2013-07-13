#include "storage/buffer_utils.h"

#include <Poco/ByteOrder.h>

namespace GraphDB {

BufferGuard::BufferGuard(size_t Size):
	data(std::malloc(Size)),
	size(Size) { }

BufferGuard::~BufferGuard() {
	std::free(this->data);
}

template <typename Key>
void writeNumber(void* buffer, Key number) {
	number = Poco::ByteOrder::toNetwork(number);

	std::memcpy(buffer, &number, sizeof(Key));
}

template <>
void writeNumber<uint8_t>(void* buffer, uint8_t number) {
	std::memcpy(buffer, &number, sizeof(uint8_t));
}

template <typename Key>
Key readNumber(const void* buffer) {
	Key number = 0;
	std::memcpy(&number, buffer, sizeof(Key));
	
	return Poco::ByteOrder::fromNetwork(number);
}

template <>
uint8_t readNumber<uint8_t>(const void* buffer) {
	uint8_t number = 0;
	std::memcpy(&number, buffer, sizeof(uint8_t));

	return number;
}

void writeString(void* buffer, std::string string) {
	std::memcpy(buffer, string.c_str(), string.length()+1);
}

std::string readString(const void* buffer) {
	return std::string(reinterpret_cast<const char*>(buffer));
}

}

#include "storage/buffer_utils.tmpl"
