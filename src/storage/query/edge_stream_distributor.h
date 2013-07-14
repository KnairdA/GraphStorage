#ifndef GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_DISTRIBUTOR_H_
#define GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_DISTRIBUTOR_H_

#include <deque>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "storage/query/edge_stream_event.h"
#include "storage/query/edge_stream_pattern.h"
#include "basic_subscription.h"

namespace GraphDB {

class EdgeStreamDistributor {
	public:
		EdgeStreamDistributor();
		~EdgeStreamDistributor();

		void publish(EdgeStreamEvent);
		void publish(const std::vector<EdgeStreamEvent>&);

		EdgeStreamPattern::Ptr getPattern(EdgeStreamRecipient*);

	private:
		void worker();
		void patternsCheckMatch(const EdgeStreamEvent&);

		std::thread thread_;
		std::atomic<bool> stop_thread_;

		std::deque<EdgeStreamEvent> event_queue_;
		std::vector<EdgeStreamPattern::Ptr> pattern_list_;

		std::mutex event_queue_mutex_;
		std::mutex pattern_list_mutex_;
		std::condition_variable new_event_notify_;
};

}

#endif  // GRAPHDB_SRC_STORAGE_QUERY_EDGE_STREAM_DISTRIBUTOR_H_
