#ifndef GRAPHDB_SRC_QUERY_LOGIC_ITERATOR_H_
#define GRAPHDB_SRC_QUERY_LOGIC_ITERATOR_H_

#include <vector>
#include <memory>

#include "exceptions.h"
#include "basic_iterator.h"
#include "storage/storage_facade.h"

namespace GraphDB {

class LogicIterator : public BasicIterator {
	public:
		typedef std::unique_ptr<LogicIterator> Ptr;

		LogicIterator(const StorageFacade*, const QueryState*);
		virtual ~LogicIterator() { };

		virtual uint32_t getCurrent();
		virtual uint32_t getNext();
		virtual bool hasNext();
		virtual bool jumpTo(uint32_t);

		template <typename Iter, typename... Args>
		Iter* getIterator(Args&&... args);

	protected:
		virtual bool iteratorsCheckCommon() = 0;
		virtual void resetBeforeJump(uint32_t) { }

		void initialize();
		std::vector<BasicIterator::Ptr>::iterator iteratorsGetMin();

		std::vector<BasicIterator::Ptr> iterators_;
		uint32_t curr_common_id_ = 0;
		bool is_initialized_     = false;

	private:
		void step();

		bool iteratorsHaveNext();
		void iteratorsGetNext();

		const StorageFacade* storage_;
		const QueryState* state_;

		bool has_next_ = true;

};

template <typename Iter, typename... Args>
Iter* LogicIterator::getIterator(Args&&... args) {
	if ( !this->is_initialized_ ) {
		this->iterators_.emplace_back(
			new Iter(this->storage_, this->state_, std::forward<Args>(args)...)
		);

		return static_cast<Iter*>(this->iterators_.back().get());
	} else {
		throw internal_iterator_exception();
	}
}

}

#endif  // GRAPHDB_SRC_QUERY_LOGIC_ITERATOR_H_
