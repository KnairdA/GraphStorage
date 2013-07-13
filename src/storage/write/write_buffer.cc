#include "storage/write/write_buffer.h"

namespace GraphDB {

WriteBuffer::~WriteBuffer() { }

void WriteBuffer::commit(StorageFacade& storage,
                         EdgeStreamDistributor& stream) {
	storage.commitBatch(this->batch_);
	stream.publish(this->event_queue_);
}

template <class Key>
void WriteBuffer::set(const Key& id, const PropertyValue& value) {
	BufferGuard valueBuffer(value.record.ByteSize());
	BufferGuard::Ptr keyBuffer(Key::toBuffer(id));

	value.record.SerializeToArray(valueBuffer.data, valueBuffer.size);

	this->batch_.Put(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer->data),
		               keyBuffer->size),
		leveldb::Slice(reinterpret_cast<char*>(valueBuffer.data),
		               valueBuffer.size)
	);
}

template <class Key>
void WriteBuffer::set(const Key& id) {
	BufferGuard::Ptr keyBuffer(Key::toBuffer(id));

	this->batch_.Put(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer->data),
		               keyBuffer->size),
		leveldb::Slice()
	);
}

template <class Key>
void WriteBuffer::remove(const Key& id) {
	BufferGuard::Ptr keyBuffer(Key::toBuffer(id));

	this->batch_.Delete(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer->data),
		               keyBuffer->size)
	);
}

}

#include "storage/write/write_buffer.tmpl"
