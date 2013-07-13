#ifndef GRAPHDB_SRC_STORAGE_PROPERTY_VALUE_H_
#define GRAPHDB_SRC_STORAGE_PROPERTY_VALUE_H_

#include <string>

#include "storage/protobuf/storage_record.pb.h"

namespace GraphDB {

struct PropertyValue {
	PropertyValue();
	PropertyValue(std::string);
	PropertyValue(uint64_t);
	PropertyValue(int64_t);
	PropertyValue(double);

	operator std::string();
	operator uint64_t();
	operator int64_t();
	operator double();

	PropertyValue& operator= (const std::string&);
	PropertyValue& operator= (const uint64_t&);
	PropertyValue& operator= (const int64_t&);
	PropertyValue& operator= (const double&);

	StorageRecord::Record record;
};

}

#endif  // GRAPHDB_SRC_STORAGE_PROPERTY_VALUE_H_
