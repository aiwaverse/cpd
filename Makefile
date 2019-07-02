main:
	clang++ -O3 -std=c++17 main.cpp movies.cpp openadr.cpp search.cpp tags.cpp trie.cpp -o database -lpthread