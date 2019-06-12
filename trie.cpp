#include "trie.hpp"
#include <iostream>

namespace trie {
int basic_node::convert_c(int c) {
    c -= '0';
    if (c > 9)
        c -= 7;
    return c;
}
std::string basic_node::transform_string(std::string in) {
    std::string out{};
    for (auto& c : in) {
        if (isalnum(c))
            out += toupper(c);
    }
    return out;
}
void basic_node::find(std::string& s) {
    std::string trans{transform_string(s)};
    _find(trans);
}
void basic_node::_find(std::string& modified) {
    if (modified.size() > 0) {
        int c{convert_c(modified[0])};
        modified.erase(modified.begin());
        if (next_nodes[c] != nullptr) {
            next_nodes[c]->_find(modified);
        }
    } else {
        cycle_array();
    }
    return;
}

void basic_node::cycle_array(void) {
    for (auto& ptr : next_nodes) {
        if (ptr) {
            if (ptr->is_word) {
                auto word = dynamic_cast<leaf_node*>(ptr.get())->word;
                auto id = dynamic_cast<leaf_node*>(ptr.get())->user_id;
                _infos.push_back({word, id});
            }
            ptr->cycle_array();
        }
    }
}

void basic_node::insert(std::string& original, unsigned id) {
    std::string new_s{transform_string(original)};
    _insert(new_s, original, id);
}
void basic_node::_insert(std::string& modified, const std::string& original, unsigned id) {
    int c{convert_c(modified.at(0))};
    if (modified.length() > 1) {
        //do the actual insertion?
        modified.erase(modified.begin());
        if (next_nodes.at(c) == nullptr) {
            next_nodes.at(c) = std::make_unique<basic_node>();
        }
        next_nodes.at(c)->_insert(modified, original, id);
    } else if (modified.length() == 1) {
        if (next_nodes.at(c) == nullptr) {
            next_nodes.at(c) = std::make_unique<leaf_node>();
            next_nodes.at(c)->_insert(modified, original, id);
        }
        return;
    }
}
void leaf_node::_insert(std::string& modified, const std::string& original, unsigned id) {
    word = original;
    user_id = id;
    is_word = true;
}
}  // namespace trie