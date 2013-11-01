#include "storage/buffer_utils.h"

#include <endian.h>

namespace GraphDB {

template <>
void writeNumber<uint64_t>(void* buffer, const uint64_t& number) {
	*reinterpret_cast<uint64_t*>(buffer) = htobe64(number);
}

template <>
void writeNumber<uint32_t>(void* buffer, const uint32_t& number) {
	*reinterpret_cast<uint32_t*>(buffer) = htobe32(number);
}

template <>
void writeNumber<uint16_t>(void* buffer, const uint16_t& number) {
	*reinterpret_cast<uint16_t*>(buffer) = htobe16(number);
}

template <>
void writeNumber<uint8_t>(void* buffer, const uint8_t& number) {
	*reinterpret_cast<uint8_t*>(buffer) = number;
}

template <>
uint64_t readNumber<uint64_t>(const void* buffer) {
	return be64toh(*reinterpret_cast<const uint64_t*>(buffer));
}

template <>
uint32_t readNumber<uint32_t>(const void* buffer) {
	return be32toh(*reinterpret_cast<const uint32_t*>(buffer));
}

template <>
uint16_t readNumber<uint16_t>(const void* buffer) {
	return be16toh(*reinterpret_cast<const uint16_t*>(buffer));
}

template <>
uint8_t readNumber<uint8_t>(const void* buffer) {
	return *reinterpret_cast<const uint8_t*>(buffer);
}

void writeString(void* buffer, const std::string& string) {
	std::memcpy(buffer, string.c_str(), string.length()+1);
}

std::string readString(const void* buffer) {
	return std::string(reinterpret_cast<const char*>(buffer));
}

}
