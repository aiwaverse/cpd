#include "ordered.hpp"
#include <iostream>
#include <stdexcept>
namespace ordered {
User_data Users::find(size_t n) {
    return users_info.at(n-1);
}
void Users::insert(size_t user, unsigned movie_id, double rating) {
    auto new_element{std::make_pair(movie_id, rating)};
    users_info.at(user-1).movie_ratings.push_back(new_element);
}
std::ostream& operator<<(std::ostream& os, const User_data& rhs){
    for(auto a:rhs.movie_ratings){
        os << "Movie id: " << a.first << ", rating: " << a.second << "\n";
    }
    return os;
}

}  // namespace ordered