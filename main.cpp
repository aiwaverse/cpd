#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include "search.hpp"
#include "tags.hpp"

//please compile with the -O3 flag, if you're insane use gcc, but this was made on clang

int main(int argc, char* argv[]) {
    Database movies{};
    std::string query{};
    do {
        std::cout << "Welcome to the Movie Lens Database, please enter your query or type help for the command list:\n";
        std::cin >> query;
        //this "cleans the screen" (actually it just scrolls a bit, still works)
        //std::cout << "\033[2J\033[1;1H";
        system("clear");
        std::cout << "======================================================================================================================================\n";
        std::string info{};
        std::getline(std::cin, info);
        for (auto& c : info)
            c = tolower(c);
        choose_query(query, info, movies);
    } while (query != "quit");
    std::cout << "aiwa thanks you <3 \n";   //yes, and very much
    return 0;
}
