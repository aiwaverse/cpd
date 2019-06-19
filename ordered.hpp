#pragma once
#include <array>
#include <vector>
#include <ostream>
namespace ordered {
struct User_data {
    //pair of id and rating
    std::vector<std::pair<unsigned, double>> movie_ratings{};
    friend std::ostream& operator<< (std::ostream& os, const User_data& rhs);
};

class Users {
   private:
    //each array element models one user, and the vector inside models all the movies rated by this user
    std::array<User_data, 138493> users_info{};
   public:
    User_data find(size_t user);
    void insert(size_t user, unsigned movie_id, double rating);
};
}  // namespace ordered