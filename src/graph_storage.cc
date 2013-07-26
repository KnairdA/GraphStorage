#include "graph_storage.h"
#include "exceptions.h"

#include "query/logic/logic_or_iterator.h"
#include "query/logic/logic_xor_iterator.h"
#include "storage/query/edge_iterator.h"
#include "query/dummy_iterator.h"

namespace GraphDB {

GraphStorage::GraphStorage(const std::string& path):
	storage_(path),
	storage_facade_(storage_),
	edge_stream_distributor_() { }

GraphStorage::GraphStorage(const std::string& path, leveldb::Options options):
	storage_(path, options),
	storage_facade_(storage_),
	edge_stream_distributor_() { }

QueryState::Ptr GraphStorage::getQueryState() const {
	return QueryState::Ptr(
		new QueryState(this->storage_)
	);
}

template <class Iter>
typename Iter::Ptr
GraphStorage::getIterator(const QueryState* state) const {
	return typename Iter::Ptr(
		new Iter(&this->storage_facade_, state)
	);
}

template <class Subscription>
typename Subscription::Ptr
GraphStorage::getSubscription(SubscriptionRecipient* parent) {
	return typename Subscription::Ptr(
		new Subscription(&this->edge_stream_distributor_,
		                 &this->storage_facade_,
		                 parent)
	);
}

void GraphStorage::commitBatch(WriteBatch* batch) {
	batch->commit(this->storage_facade_,
	              this->edge_stream_distributor_);
}

template <IdentifierType KeyType, typename ValueType>
ValueType GraphStorage::resolveIdentifier(std::string name,
                                          PropertyValue& property) {
	if ( this->storage_facade_.get<IdentifierId>(IdentifierId(KeyType, name),
	                                             property) ) {
		return static_cast<ValueType>(
			static_cast<uint64_t>(property)
		);
	} else {
		throw storage_record_exception();
	}
}

}

#include "graph_storage.tmpl"
