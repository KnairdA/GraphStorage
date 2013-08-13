#ifndef GRAPHDB_EXCEPTIONS_H_
#define GRAPHDB_EXCEPTIONS_H_

#include <exception>

namespace GraphDB {

class storage_exception: public std::exception {
	virtual const char* what() const throw() {
		return "storage";
	}
};

class storage_record_exception: public storage_exception {
	virtual const char* what() const throw() {
		return "storage_record";
	}
};

class storage_section_exception: public storage_exception {
	virtual const char* what() const throw() {
		return "storage_section";
	}
};

class storage_state_exception: public storage_exception {
	virtual const char* what() const throw() {
		return "storage_state";
	}
};

class storage_transaction_exception: public storage_exception {
	virtual const char* what() const throw() {
		return "storage_transaction";
	}
};

class graph_exception: public std::exception {
	virtual const char* what() const throw() {
		return "graph";
	}
};

class graph_maintenance_exception: public graph_exception {
	virtual const char* what() const throw() {
		return "graph_maintenance";
	}
};

class graph_query_exception: public graph_exception {
	virtual const char* what() const throw() {
		return "graph_query";
	}
};

class query_logic_exception: public graph_query_exception {
	virtual const char* what() const throw() {
		return "query_logic";
	}
};

class query_internal_exception: public graph_query_exception {
	virtual const char* what() const throw() {
		return "query_internal";
	}
};

class internal_iterator_exception: public query_internal_exception {
	virtual const char* what() const throw() {
		return "internal_iterator";
	}
};

class buffer_size_exception : public std::exception {
	virtual const char* what() const throw() {
		return "buffer_size";
	}
};

}

#endif  // GRAPHDB_EXCEPTIONS_H_
