#pragma once
#include <array>
#include <memory>
#include <string>

namespace trie {
class basic_node {
   protected:
    std::array<std::unique_ptr<basic_node>, 36> next_nodes{};
    bool is_word{false};
    std::string transform_string(std::string);
    int convert_c(int c);

   public:
    basic_node(){};
    basic_node(bool b) : is_word(b){};
    void cycle_array(void);
    void find(std::string&);
    void _find(std::string& modified);
    void insert(std::string& word, unsigned id);
    virtual void _insert(std::string& modified, const std::string& original, unsigned id);
    virtual ~basic_node(){};
};
class leaf_node : public basic_node {
   protected:
    void _insert(std::string& modified, const std::string& original, unsigned id) override;

   public:
    std::string word{};
    unsigned user_id{};
    leaf_node(){};
    virtual ~leaf_node(){};
};
}  // namespace trie