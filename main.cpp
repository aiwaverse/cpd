#include <chrono>
#include <iostream>
#include <limits>
#include "movies.hpp"
#include "tags.hpp"

int main(int argc, char* argv[]) {
    using namespace std::chrono;
    /*Database test{};
    test.read_tags_file();
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
    }while(op != 'N');*/
    std::cout << "Aiwa thanks you <3 \n";
    return 0;
}
