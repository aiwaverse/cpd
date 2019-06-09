#pragma once
#include "openadr.hpp"
#include "ordered.hpp"
#include "trie.hpp"
#include <sstream>

class Database {
   private:
    trie::basic_node movie_names{};
    open::Hash_Table movie_data{};
    ordered::Users ratings{};

   public:
    void tree_insert(std::string& s, unsigned id);
    void hash_insert(const std::vector<std::string>& genre_list, unsigned movie_id);
    void array_insert(size_t user, unsigned movie_id, double rating);
    void read_movie_file(void);
    void read_ratings_file(void);
    void search_word(std::string& s);

};
std::string parse_genres(std::string& s);
std::string parse_quoted_line(std::string& s);
std::string parse_line(const std::string& s, unsigned info);
void clear_buffer(void);
std::string unquote( const std::string& s );
std::vector<std::string> make_string_vector(const std::string& s);
inline void fill_rating_field(std::string& s, int& user_id, int& movie_id, double& rating);