#pragma once
#include "openadr.hpp"
#include "ordered.hpp"
#include "trie.hpp"
#include "tags.hpp"
#include <sstream>

class Database {
   private:
    static constexpr const char* default_ratings_file = "Dados/rating.csv";
    trie::basic_node movie_names{};
    open::Hash_Table movie_data{};
    ordered::Users ratings{};
    tag::Hash_Table movie_tags{};
    void read_movie_file(void);
    void read_ratings_file(std::string rating_file);

   public:
    void read_tags_file(void);
    Database(std::string file_name = default_ratings_file);
    void search_word(std::string& s);
    void search_tag(const std::string&);
    void print_search(std::vector<std::pair<std::string, unsigned>>);
    void print_search(const std::vector<unsigned>&);
    void search_user(unsigned id);
    void search_tag(const std::vector<std::string>&);
    void search_top(const std::string&, unsigned);

};
std::string parse_genres(std::string& s);
std::string parse_quoted_line(std::string& s);
std::string parse_line(const std::string& s, unsigned info);
void clear_buffer(void);
std::string unquote( const std::string& s );
std::vector<std::string> make_string_vector(const std::string& s);
void fill_rating_field(std::string& s, int& user_id, int& movie_id, double& rating);
std::string string_print(std::string& s);
int unicode_count(const std::string&);