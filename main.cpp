#include <chrono>
#include <iostream>
#include <limits>
#include "movies.hpp"

int main(int argc, char* argv[]) {
    using namespace std::chrono;
    Database test{};
    test.read_movie_file();
    std::cout << "Trie made\n";
    auto start = system_clock::now();
    test.read_ratings_file();
    auto stop = system_clock::now();
    std::cout << "Ratings added\n";
    std::cout << duration_cast<seconds>(stop - start).count() << " s\n";
    char op{};
    do{
        std::cout << "Y for another read, N to leave\n";
        std::cin >> op;
        clear_buffer();
        op = toupper(op);
        if(op == 'Y'){
            std::cout << "Please enter the string: ";
            std::string search{};
            std::getline(std::cin, search);
            system("clear");
            test.search_word(search);
        }
    }while(op != 'N');
    std::cout << "Aiwa thanks you <3 \n";
    return 0;
}
