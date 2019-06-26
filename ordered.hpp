#pragma once
#include <array>
#include <ostream>
#include <vector>
namespace ordered {
struct User_data {
    //pair of id and rating
    std::vector<std::pair<unsigned, double>> movie_ratings{};
};

class Users {
   private:
    //each array element models one user, and the vector inside models all the movies rated by this user
    std::array<User_data, 138493> users_info{};

   public:
    User_data find(size_t user) { return users_info.at(user - 1); };
    void insert(size_t user, unsigned movie_id, double rating) { users_info[user - 1].movie_ratings.push_back({movie_id, rating}); };
};
}  // namespace ordered