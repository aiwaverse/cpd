#include "tags.hpp"
namespace tag {

size_t Hash_Table::mapping(const std::string& s) {
    size_t i{0};
    uint32_t hash{0};
    while (i != s.size()) {
        hash += s.at(i++);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}
//probing functions
size_t Hash_Table::double_probing(size_t c, const unsigned i) {
    return c + i * (29 - (c % 7));
}

bool Hash_Table::test_for_tag(size_t pos, unsigned id) {
    auto find_result = std::find(table[pos]._movies.begin(), table[pos]._movies.end(), id);
    if (find_result != table[pos]._movies.end())
        return true;
    return false;
}

bool Hash_Table::insert(std::string s, unsigned id) {
    size_t i{0};
    size_t key{mapping(s)};
    auto o_key{key};
    size_t pos{key % table.size()};
    auto fpos{pos};
    while (true) {
        if (table.at(pos).occupied() == false)  //if the space is availabe
            break;
        //remove first condition
        if (table.at(pos).key() == static_cast<size_t>(key)) {  //if the key at the position is the same, the element is the same
            if (test_for_tag(pos, id) == false)
                table.at(pos)._movies.push_back(id);
            return true;
        }
        ++i;
        key = double_probing(o_key, i);  //o_key is to use the original key in the function and not the new key
        pos = key % table.size();
        if (pos == fpos)
            return false;
    }
    table.at(pos).set_key(key);
    table.at(pos).set_occupied(true);
    table.at(pos)._movies.push_back(id);
    table.at(pos).set_used(true);
    return true;
}

std::vector<unsigned> Hash_Table::find(std::string s) {
    size_t i{0};
    size_t key{mapping(s)};
    auto o_key{key};
    size_t pos{key % table.size()};
    while (table.at(pos).used() == true) {
        if (table.at(pos).key() == key)  //if the space is availabe
            return table.at(pos)._movies;
        ++i;
        key = double_probing(o_key, i);
        pos = key % table.size();
    }
    return {};
}
}  // namespace tag