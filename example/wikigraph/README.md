# Example: Wikipedia Link Graph

This directory contains an example of how the GraphStorage library can be used to query a graph of all links between Wikipedia pages.

## Dataset

* [links-simple-sorted.zip](http://users.on.net/%7Ehenry/pagerank/links-simple-sorted.zip)
* [titles-sorted.zip](http://users.on.net/%7Ehenry/pagerank/titles-sorted.zip)

## Import

After compiling the example application using `make` you will find a `import` executable that may be used to import the dataset files from the dataset subdirectory into a new graph.

The directed relationships between the pages are stored under edge type 4. Page titles are stored under property type 1.

## Query

The query performed by the `query` executable returns all endangered mammals which reside in Europe or North America.
This is achived by aggregating all mammals of Europe and North America into a single iterator using the `LogicOrIterator`.
This iterator is then filtered against all endangered animals by using the `LogicAndIterator`.
Note that the resulting list / iterator is also filtered against the active node relationship and the type 1 `PropertyIterator` so that only nodes that contain the title property are returned by the query.
