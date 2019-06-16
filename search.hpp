#pragma once
#include <string>
#include "movies.hpp"


void choose_query(const std::string& first, const std::string& line, Database& obj);
void title_query(const std::string& title, Database& obj);
void topN_query(const std::string& genre, unsigned n, Database& obj);
void tag_query(const std::string& tags, Database& obj);
void user_query(const std::string& user, Database& obj);