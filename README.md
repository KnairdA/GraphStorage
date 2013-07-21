# GraphStorage

... is a Graph storage and query library based on LevelDB.

It currently supports integer indexed nodes with properties and directed edges with types.
The integer IDs are serialized 'by hand', values are serialized using protocol buffers.
Everything is stored in a single sorted LevelDB database.

Queries are possible trough a iterator like interface that handles single level queries quite fast.
Additionally changes to edges can be monitored using a subscription mechanism.

## Requirements

* C++ compiler with support for C++11 (tested with current versions of GCC and clang on Linux)
* Google Protobuf
* Google LevelDB
* Poco ByteOrder header

## State

This library is in development and is not intended for any kind of production usage.
