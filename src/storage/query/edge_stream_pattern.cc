#include "storage/query/edge_stream_pattern.h"

namespace GraphDB {

EdgeStreamPattern::EdgeStreamPattern(EdgeStreamRecipient *recipient) {
	this->recipient_ = recipient;
}

bool EdgeStreamPattern::evaluate(const EdgeStreamEvent& event) {
	if ( this->isMatchingPattern(event) ) {
		this->recipient_->pushNext(event);
		return true;
	} else {
		return false;
	}
}

bool EdgeStreamPattern::isMatchingPattern(const EdgeStreamEvent& event) {
	if ( (this->from_id_set_   && this->edge_.fromId    != event.Edge.fromId)    ||
	     (this->type_id_set_   && this->edge_.typeId    != event.Edge.typeId)    ||
	     (this->direction_set_ && this->edge_.direction != event.Edge.direction) ||
	     (this->to_id_set_     && this->edge_.toId      != event.Edge.toId) ) {
		return false;
	} else {
		return true;
	}
}

void EdgeStreamPattern::setFromId(uint32_t fromId) {
	this->edge_.fromId = fromId;
	this->from_id_set_ = true;
}

void EdgeStreamPattern::setTypeId(uint16_t typeId) {
	this->edge_.typeId = typeId;
	this->type_id_set_ = true;
}

void EdgeStreamPattern::setDirection(EdgeDirection direction) {
	this->edge_.direction = direction;
	this->direction_set_  = true;
}

void EdgeStreamPattern::setToId(uint32_t toId) {
	this->edge_.toId = toId;
	this->to_id_set_ = true;
}

}
