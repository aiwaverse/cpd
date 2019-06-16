#include <vector>

template <class T>
std::vector<T> intersection(const std::vector<T>& v1, const std::vector<T>& v2){
    //get the least amount of traversal
    auto min {v1.size() < v2.size() ? v1.size() : v2.size()};
    std::vector<T> r_vec{};
    for(size_t i{}; i < min; ++i){
        if(std::find(v2.begin(), v2.end(), v1.at(i)) != v2.end())
            r_vec.push_back(v1.at(i));
    }
    return r_vec;
}