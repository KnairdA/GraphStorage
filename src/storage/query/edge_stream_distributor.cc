#include "storage/query/edge_stream_distributor.h"

#include <algorithm>

namespace GraphDB {

EdgeStreamDistributor::EdgeStreamDistributor():
	stop_thread_(false) {
	this->thread_ = std::thread([this]() {
		this->worker();
	});
}

EdgeStreamDistributor::~EdgeStreamDistributor() {
	this->stop_thread_ = true;
	this->new_event_notify_.notify_all();
	this->thread_.join();
}

void EdgeStreamDistributor::publish(EdgeStreamEvent event) {
	std::lock_guard<std::mutex> lock(this->event_queue_mutex_);

	this->event_queue_.push_back(event);
	this->new_event_notify_.notify_one();
}

void EdgeStreamDistributor::publish(
	const std::vector<EdgeStreamEvent>& events) {
	std::lock_guard<std::mutex> lock(this->event_queue_mutex_);

	for ( const EdgeStreamEvent& event : events ) {
		this->event_queue_.push_back(event);
	}

	this->new_event_notify_.notify_one();
}

EdgeStreamPatternPtr EdgeStreamDistributor::getPattern(
	EdgeStreamRecipient* recipient) {
	std::lock_guard<std::mutex> lock(this->pattern_list_mutex_);

	this->pattern_list_.emplace_back(new EdgeStreamPattern(recipient));

	return std::shared_ptr<EdgeStreamPattern>(this->pattern_list_.back());
}

void EdgeStreamDistributor::worker() {
	while ( !this->stop_thread_ ) {
		std::unique_lock<std::mutex> lock(this->event_queue_mutex_);

		this->new_event_notify_.wait(lock, [this] {
			return !this->event_queue_.empty() || this->stop_thread_;
		});

		if ( !this->event_queue_.empty() ) {
			EdgeStreamEvent event = this->event_queue_.front();
			this->event_queue_.pop_front();

			lock.unlock();

			this->patternsCheckMatch(event);
		} else {
			lock.unlock();
		}
	}
}

void EdgeStreamDistributor::patternsCheckMatch(const EdgeStreamEvent& event) {
	std::lock_guard<std::mutex> lock(this->pattern_list_mutex_);

	/*this->pattern_list_.erase(
		std::remove_if(this->pattern_list_.begin(),
		               this->pattern_list_.end(),
		               [](EdgeStreamPatternPtr &p) -> bool {
		                   return p.unique();
		               })
	);*/

	std::for_each(this->pattern_list_.begin(),
	              this->pattern_list_.end(),
	              [&event](EdgeStreamPatternPtr &p) {
	                  p->evaluate(event);
	              });
}

}
