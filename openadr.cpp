#include "openadr.hpp"
namespace open {
//probing functions
size_t Hash_Table::double_probing(size_t c, const unsigned i) {
    return c + i * (29 - (c % 7));
    //return c + (i*i);
}
size_t Hash_Table::linear_probing(size_t c, const unsigned i) {
    return c + i;
}
unsigned Hash_Table::hash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned Hash_Table::unhash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = (x >> 16) ^ x;
    return x;
}

bool Hash_Table::insert(open::movie_data& data, size_t id) {
    size_t i{0};
    size_t key{hash(id)};
    auto o_key{key};
    size_t pos{key % table.size()};
    auto fpos{pos};
    while (true) {
        if (table[pos].occupied() == false)  //if the space is availabe
            break;
        //remove first condition
        if (table[pos].key() == static_cast<size_t>(key))  //if the key at the position is the same, the element is the same
            return false;
        ++i;
        key = double_probing(o_key, i);  //o_key is to use the original key in the function and not the new key
        pos = key % table.size();
        if (pos == fpos)
            return false;
    }
    table[pos].set_key(key);
    table[pos].set_occupied(true);
    table[pos].set_data(data);
    table[pos].set_used(true);
    return true;
}

movie_data Hash_Table::find(size_t to_find) {
    size_t i{0};
    size_t key{hash(to_find)};
    auto o_key{key};
    size_t pos{key % table.size()};
    while (table.at(pos).used() == true) {
        if (table.at(pos).key() == key)  //if the space is availabe
            return table.at(pos).data();
        ++i;
        key = double_probing(o_key, i);
        pos = key % table.size();
    }
    return movie_data{};
}

void Hash_Table::add_rating(size_t to_find, double rating) {
    size_t i{0};
    size_t key{hash(to_find)};
    auto o_key{key};
    size_t pos{key % table.size()};
    while (table[pos].used() == true) {
        if (table[pos].key() == key) {  //if movie is found
            table[pos]._content.all_ratings+=rating;
            ++table[pos]._content.number_of_ratings;
        }
        ++i;
        key = double_probing(o_key, i);
        pos = key % table.size();
    }
}
}  // namespace open