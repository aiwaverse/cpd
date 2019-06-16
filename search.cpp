#include "search.hpp"

#include <iostream>

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
        topN_query(line, std::stoi(number), obj);
    } else
        return;
}

void title_query(const std::string& title, Database& obj) {
    obj.search_word(const_cast<std::string&>(title));
}
void topN_query(const std::string& genre, unsigned n, Database& obj) {
    std::cout << "got to topN query with genre: " << genre << " and n: " << n << "\n";
}
void tag_query(const std::string& tags, Database& obj) {
    std::cout << "got to tag query with tags: " << tags << "\n";
}
void user_query(const std::string& user, Database& obj) {
    unsigned user_id {std::stoi(user)};
}