#include "storage/property_value.h"
#include "exceptions.h"

using namespace ::GraphDB::StorageRecord;

namespace GraphDB {

PropertyValue::PropertyValue() {
	this->record.set_type(Record_Type::Record_Type_EMPTY);
}

PropertyValue::PropertyValue(std::string value) {
	this->record.set_type(Record_Type::Record_Type_STRING);
	this->record.MutableExtension(StringRecord::record)->set_content(value);
}

PropertyValue::PropertyValue(uint64_t value) {
	this->record.set_type(Record_Type::Record_Type_UINT64);
	this->record.MutableExtension(UInt64Record::record)->set_content(value);
}

PropertyValue::PropertyValue(int64_t value) {
	this->record.set_type(Record_Type::Record_Type_INT64);
	this->record.MutableExtension(Int64Record::record)->set_content(value);
}

PropertyValue::PropertyValue(double value) {
	this->record.set_type(Record_Type::Record_Type_DOUBLE);
	this->record.MutableExtension(DoubleRecord::record)->set_content(value);
}

PropertyValue::operator std::string() {
	switch ( this->record.type() ) {
		case Record_Type::Record_Type_STRING: {
			return this->record.MutableExtension(
				StringRecord::record
			)->content();
		}
		case Record_Type::Record_Type_UINT64: {
			return std::to_string(this->record.MutableExtension(
				UInt64Record::record
			)->content());
		}
		case Record_Type::Record_Type_INT64: {
			return std::to_string(this->record.MutableExtension(
				Int64Record::record
			)->content());
		}
		case Record_Type::Record_Type_DOUBLE: {
			return std::to_string(this->record.MutableExtension(
				DoubleRecord::record
			)->content());
		}
		default: {
			return std::string();
		}
	}
}

PropertyValue::operator uint64_t() {
	if ( this->record.type() == Record_Type::Record_Type_UINT64 ) {
		return this->record.MutableExtension(UInt64Record::record)->content();
	} else {
		throw storage_record_exception();
	}
}

PropertyValue::operator int64_t() {
	if ( this->record.type() == Record_Type::Record_Type_INT64 ) {
		return this->record.MutableExtension(Int64Record::record)->content();
	} else {
		throw storage_record_exception();
	}
}

PropertyValue::operator double() {
	if ( this->record.type() == Record_Type::Record_Type_DOUBLE ) {
		return this->record.MutableExtension(DoubleRecord::record)->content();
	} else {
		throw storage_record_exception();
	}
}

PropertyValue& PropertyValue::operator= (const std::string& value) {
	this->record.set_type(Record_Type::Record_Type_STRING);
	this->record.MutableExtension(StringRecord::record)->set_content(value);

	return *this;
}

PropertyValue& PropertyValue::operator= (const uint64_t& value) {
	this->record.set_type(Record_Type::Record_Type_UINT64);
	this->record.MutableExtension(UInt64Record::record)->set_content(value);

	return *this;
}

PropertyValue& PropertyValue::operator= (const int64_t& value) {
	this->record.set_type(Record_Type::Record_Type_INT64);
	this->record.MutableExtension(Int64Record::record)->set_content(value);

	return *this;
}

PropertyValue& PropertyValue::operator= (const double& value) {
	this->record.set_type(Record_Type::Record_Type_DOUBLE);
	this->record.MutableExtension(DoubleRecord::record)->set_content(value);

	return *this;
}

}
