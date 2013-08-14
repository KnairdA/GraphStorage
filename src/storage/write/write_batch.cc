#include "storage/write/write_batch.h"

namespace GraphDB {

WriteBatch::~WriteBatch() { }

void WriteBatch::commit(StorageFacade& storage,
                         EdgeStreamDistributor& stream) {
	storage.commitBatch(this->batch_);
	stream.publish(this->event_queue_);
}

template <class Key>
void WriteBatch::set(const Key& id, const PropertyValue& value) {
	BufferGuard<NullBuffer> valueBuffer;
	valueBuffer.resize(value.record.ByteSize());

	BufferGuard<Key> keyBuffer;
	Key::toBuffer(id, keyBuffer);

	value.record.SerializeToArray(valueBuffer.data, valueBuffer.size);

	this->batch_.Put(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer.data),
		               keyBuffer.size),
		leveldb::Slice(reinterpret_cast<char*>(valueBuffer.data),
		               valueBuffer.size)
	);
}

template <class Key>
void WriteBatch::set(const Key& id) {
	BufferGuard<Key> keyBuffer;
	Key::toBuffer(id, keyBuffer);

	this->batch_.Put(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer.data),
		               keyBuffer.size),
		leveldb::Slice()
	);
}

template <class Key>
void WriteBatch::remove(const Key& id) {
	BufferGuard<Key> keyBuffer;
	Key::toBuffer(id, keyBuffer);

	this->batch_.Delete(
		leveldb::Slice(reinterpret_cast<char*>(keyBuffer.data),
		               keyBuffer.size)
	);
}

}

#include "storage/write/write_batch.tmpl"
