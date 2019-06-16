#pragma once
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
namespace tag {
class Hash_N {
    friend class Hash_Table;
   private:
    std::vector<unsigned> _movies{};
    size_t _key{0};
    bool _occupied{false};
    bool _used{false};

   public:
    // constructors
    Hash_N() = default;
    Hash_N(const Hash_N&) = default;
    Hash_N(Hash_N&&) = default;
    //functions to return the elements
    size_t key(void) { return _key; };
    bool occupied(void) { return _occupied; };
    bool used(void) { return _used; };
    std::vector<unsigned> movies(void) { return _movies; };
    void set_key(long k) { _key = k; };
    void set_occupied(bool b) { _occupied = b; };
    void set_used(bool b) { _used = b; };
};
class Hash_Table {
    friend class Hash_N;
   private:
    std::vector<Hash_N> table{};
    //mapping of strings to size_t and probings
    size_t mapping(const std::string&);
    size_t double_probing(size_t, const unsigned);  //double probing and not double hashing to keep a pattern
    bool test_for_tag(size_t pos, unsigned id);

   public:
    Hash_Table(void) : table(620773){};
    Hash_Table(const Hash_Table&) = default;
    Hash_Table(Hash_Table&&) = default;
    bool insert(std::string, unsigned id);
    std::vector<unsigned> find(const std::string&);
    void print(std::ofstream& os);
    void print(void);
};

}  //namespace open