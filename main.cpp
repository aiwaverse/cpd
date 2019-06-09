#include <iostream>
#include "movies.hpp"
#include <limits>
#include <chrono>

int main(int argc, char* argv[]) {
    using namespace std::chrono;
    Database test{};
    test.read_movie_file();
    std::cout << "Trie made\n";
    auto start = system_clock::now();
    test.read_ratings_file();
    auto stop = system_clock::now();
    std::cout << "Ratings added\n";
    std::cout << duration_cast<seconds>(stop-start).count() << " s\n";
    std::cout << "Aiwa thanks you <3 \n";
    return 0;
}
