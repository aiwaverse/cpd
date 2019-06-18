#include "search.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iomanip>

void choose_query(const std::string& first, const std::string& line, Database& obj) {
    if (first == "movie")
        title_query(line, obj);
    else if (first == "user")
        user_query(line, obj);
    else if (first == "tags")
        tag_query(line, obj);
    else if (first.find("top") != std::string::npos) {
        auto pos = first.find("top");
        pos += 3;
        std::string number{};
        for (size_t i{pos}; i < first.size(); ++i)
            number += first.at(i);
        try {
            topN_query(line, std::stoi(number), obj);
        } catch (std::invalid_argument) {
            std::cout << "Please check the top<N> syntax\n";
        }
    } else if (first == "help") {
        std::cout << "Valid inputs:\n";
        std::cout <<"\tmovie <movie name or prefix>\n"
                  <<"\tuser <id>\n"
                  <<"\ttop<number> '<genre>'\n"
                  <<"\ttags '<tag>' (any number of tags)\n"
                  <<"\tquit\n";
    } else if (first == "quit")
        return;
    else {
        std::cout << "Invalid input, please check\n";
        return;
    }
}

void title_query(const std::string& title, Database& obj) {
    obj.search_word(const_cast<std::string&>(title));
}
void topN_query(const std::string& genre, unsigned n, Database& obj) {
    std::istringstream iss{genre};
    std::string token{};
    while (iss >> std::quoted(token, '\'')) {
        std::string actual_genre{};
        std::transform(token.begin(), token.end(), std::back_inserter(actual_genre), ::tolower);
        obj.search_top(actual_genre, n);
    }
    return;
}
void tag_query(const std::string& tags, Database& obj) {
    std::istringstream iss{tags};
    std::string token{};
    std::vector<std::string> all_tags{};
    while (iss >> std::quoted(token, '\'')) {
        token = trie::transform_string(token);
        all_tags.push_back(token);
    }
    obj.search_tag(all_tags);
}
void user_query(const std::string& user, Database& obj) {
    int user_id{std::stoi(user)};
    try {
        obj.search_user(user_id);
    } catch (std::out_of_range) {
        std::cout << "Please use a valid user id\n";
    }
}
