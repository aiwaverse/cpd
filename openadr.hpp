#pragma once
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
namespace open {

struct movie_data {
    unsigned number_of_ratings{};
    double all_ratings{};
    std::vector<std::string> genres{};
    std::string name{};
    friend std::ostream& operator<<(std::ostream& os,const movie_data& rhs);
};

inline std::ostream& operator<<(std::ostream& os,const movie_data& rhs){
    os << "Rating: " << rhs.all_ratings/rhs.number_of_ratings << "\n";
    for(auto& g: rhs.genres){
        os << g << " ";
    }
    os << std::endl;
    return os;
}

class Hash_N {
    friend class Hash_Table;
   private:  //change to private
    movie_data _content{};
    size_t _key{0};
    bool _occupied{false};
    bool _used{false};

   public:
    // constructors
    Hash_N(movie_data s) : _content{s} {};
    Hash_N() = default;
    Hash_N(const Hash_N&) = default;
    Hash_N(Hash_N&&) = default;
    //functions to return the elements
    size_t key(void) { return _key; };
    bool occupied(void) { return _occupied; };
    bool used(void) { return _used; };
    movie_data data(void) { return _content; };
    void set_key(long k) { _key = k; };
    void set_occupied(bool b) { _occupied = b; };
    void set_used(bool b) { _used = b; };
    void set_data(movie_data& s) { _content = s; };
};
class Hash_Table {
   private:  //change to private
    std::vector<Hash_N> table{};
    const unsigned size_of_table{36529};
    //mapping of strings to size_t and probings
    size_t linear_probing(size_t, const unsigned);
    size_t double_probing(size_t, const unsigned);  //double probing and not double hashing to keep a pattern
    unsigned hash(unsigned);
    unsigned unhash(unsigned x);
   public:
    Hash_Table() { table.resize(size_of_table); }
    Hash_Table(const Hash_Table&) = default;
    Hash_Table(Hash_Table&&) = default;
    bool insert(movie_data& data, size_t id);
    movie_data find(size_t to_find);
    void add_rating(size_t to_find, double rating);
    void print(std::ofstream& os);
    void print(void);
};

}  //namespace open