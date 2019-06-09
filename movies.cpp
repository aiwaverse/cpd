#include "movies.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <limits>

void Database::tree_insert(std::string& s, unsigned id) {
    movie_names.insert(s, id);
}
void Database::hash_insert(const std::vector<std::string>& genre_list, unsigned movie_id) {
    open::movie_data new_movie{0, 0.0, genre_list};
    movie_data.insert(new_movie, movie_id);
}

void Database::read_movie_file(void) {
    std::ifstream movie("../Dados/movie.csv");
    if (not movie) {
        throw std::runtime_error("Incorrect movie.csv file");
    }
    std::string movie_string{};
    std::getline(movie, movie_string);  //to get rid of the first line (names)
    while (std::getline(movie, movie_string)) {
        int id{std::stoi(parse_line(movie_string, 1))};
        std::string name{parse_quoted_line(movie_string)};
        movie_names.insert(name, id);
        //genres need the new line starting at the section
        std::string genres{parse_genres(movie_string)};
        genres = unquote(genres);
        auto genre_list{make_string_vector(genres)};
        open::movie_data data{0, 0, genre_list, name};
        movie_data.insert(data, id);
    }
    movie.close();
}

void Database::read_ratings_file(void) {
    using namespace std::chrono;
    std::ifstream rating("../Dados/rating.csv");  //change this to test the full file
    if (not rating) {
        throw std::runtime_error("Incorrect rating.csv file");
    }
    std::string file_line{};
    std::getline(rating, file_line);  //get the first dumb line
    file_line.clear();
    unsigned i{};
    while (std::getline(rating, file_line)) {
        int user_id{};
        int movie_id{};
        double movie_rating{};
        fill_rating_field(file_line,user_id, movie_id, movie_rating);
        movie_data.add_rating(movie_id, movie_rating);        //add the read rating on the hash
        ratings.insert(user_id - 1, movie_id, movie_rating);  //add the new rating to the ordered array
    }
    rating.close();
}

inline void fill_rating_field(std::string& s, int& user_id, int& movie_id, double& rating){
        std::istringstream iss{s};
        std::string token{};
        std::getline(iss, token, ',');
        user_id = std::stoi(token);
        iss.clear();
        iss.str(token);
        std::getline(iss, token, ',');
        movie_id = std::stoi(token);
        iss.clear();
        iss.str(token);
        std::getline(iss, token, ',');
        rating = std::stod(token);
}

void Database::search_word(std::string& s) {
    movie_names.find(s);
}

std::string parse_line(const std::string& s, unsigned info) {
    std::stringstream iss{s};
    std::string extracted{};
    unsigned i{};
    while (i < info and std::getline(iss, extracted, ',')) {
        ++i;
    }
    return extracted;
}

std::string parse_genres(std::string& s) {
    auto pos = s.rfind(",\"");
    std::string new_s(s.begin() + pos + 2, s.end() - 2);
    return new_s;
}

std::string parse_quoted_line(std::string& s) {
    auto first = s.find(",\"");
    std::string s2(s.begin() + first + 2, s.end());
    auto last = s2.find("\",");
    std::string new_s(s2.begin(), s2.begin() + last);
    return new_s;
}

void clear_buffer(void) {
    using namespace std;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

std::string unquote(const std::string& s) {
    std::string result;
    std::istringstream ss(s);
    ss >> std::quoted(result);
    return result;
}
std::vector<std::string> make_string_vector(const std::string& s) {
    std::stringstream iss{s};
    std::string part{};
    std::vector<std::string> svec{};
    if (s == "(no genres listed)")
        return svec;
    while (std::getline(iss, part, '|')) {
        svec.push_back(part);
    }
    return svec;
}