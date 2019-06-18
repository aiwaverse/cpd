#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include "search.hpp"
#include "tags.hpp"

//please compile with the -O3 flag, if you're insane use gcc, but this was made on clang

int main(int argc, char* argv[]) {
    Database movies{};
    /*
    char op{};
    do{
        std::cout << "Y for another read, N to leave\n";
        std::cin >> op;
        clear_buffer();
        system("clear");
        op = toupper(op);
        if(op == 'Y'){
            std::cout << "Please enter the string: ";
            std::string first_word{}, rest{};
            std::cin >> first_word;
            std::getline(std::cin, rest);
            choose_query(first_word, rest, movies);
        }
    }while(op != 'N'); */
    std::string query{};
    do {
        std::cout << "Welcome to the Movie Lens Database, please enter your query or type help for the command list:\n";
        std::cin >> query;
        std::cout << "\033[2J\033[1;1H";
        std::string info{};
        std::getline(std::cin, info);
        for (auto& c : info)
            c = tolower(c);
        choose_query(query, info, movies);
    } while (query != "quit");
    std::cout << "Aiwa thanks you <3 \n";
    return 0;
}
