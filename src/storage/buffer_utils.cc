#include "storage/buffer_utils.h"

#include <endian.h>

namespace GraphDB {

BufferGuard::BufferGuard(size_t Size):
	data(std::malloc(Size)),
	size(Size) { }

BufferGuard::~BufferGuard() {
	std::free(this->data);
}

template <>
void writeNumber<uint64_t>(void* buffer, uint64_t number) {
	number = htobe64(number);

	std::memcpy(buffer, &number, sizeof(uint64_t));
}

template <>
void writeNumber<uint32_t>(void* buffer, uint32_t number) {
	number = htobe32(number);

	std::memcpy(buffer, &number, sizeof(uint32_t));
}

template <>
void writeNumber<uint16_t>(void* buffer, uint16_t number) {
	number = htobe16(number);

	std::memcpy(buffer, &number, sizeof(uint16_t));
}

template <>
void writeNumber<uint8_t>(void* buffer, uint8_t number) {
	std::memcpy(buffer, &number, sizeof(uint8_t));
}

template <>
uint64_t readNumber<uint64_t>(const void* buffer) {
	uint64_t number = 0;
	std::memcpy(&number, buffer, sizeof(uint64_t));
	
	return be64toh(number);
}

template <>
uint32_t readNumber<uint32_t>(const void* buffer) {
	uint32_t number = 0;
	std::memcpy(&number, buffer, sizeof(uint32_t));
	
	return be32toh(number);
}

template <>
uint16_t readNumber<uint16_t>(const void* buffer) {
	uint16_t number = 0;
	std::memcpy(&number, buffer, sizeof(uint16_t));
	
	return be16toh(number);
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
