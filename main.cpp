#include <chrono>
#include <iostream>
#include <limits>
#include "tags.hpp"
#include "search.hpp"

int main(int argc, char* argv[]) {
    Database test{};

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
            choose_query(first_word, rest, test);
        }
    }while(op != 'N');
    std::cout << "Aiwa thanks you <3 \n";
    return 0;
}
