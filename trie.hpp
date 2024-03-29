#pragma once
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace trie {
class basic_node {
   private:
    static std::vector<std::pair<std::string, int>> _infos;

   protected:
    std::array<std::unique_ptr<basic_node>, 36> next_nodes{};
    bool is_word{false};
    int convert_c(int c);

   public:
    basic_node(){};
    basic_node(bool b) : is_word(b){};
    void cycle_array(void);
    void find(std::string&);
    void _find(std::string& modified);
    void insert(std::string& word, int id);
    void clear(void) { _infos.clear(); };
    std::vector<std::pair<std::string, int>> infos(void) { return _infos; };
    virtual void _insert(std::string& modified, const std::string& original, int id);
    virtual ~basic_node(){};
};
class leaf_node : public basic_node {
   protected:
    void _insert(std::string& modified, const std::string& original, int id) override;

   public:
    std::string word{};
    int user_id{};
    leaf_node(){};
    virtual ~leaf_node(){};
};
std::string transform_string(std::string);
inline std::vector<std::pair<std::string, int>> basic_node::_infos{};  //static member initialization
}  // namespace trie