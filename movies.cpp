#include "movies.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <limits>

Database::Database(std::string file_name){
    std::cout << "Starting trie construction:\n";
    read_movie_file();
    std::cout << "Trie finished construction:\n";
    std::cout << "Starting hash construction:\n";
    read_ratings_file(file_name);
    std::cout << "Hash finished construction:\n";
}
void Database::tree_insert(std::string& s, unsigned id) {
    movie_names.insert(s, id);
}
void Database::hash_insert(const std::vector<std::string>& genre_list, unsigned movie_id) {
    open::movie_data new_movie{0, 0.0, genre_list};
    movie_data.insert(new_movie, movie_id);
}

void Database::read_movie_file(void) {
    std::ifstream movie("Dados/movie.csv");
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

void Database::read_ratings_file(std::string rating_file) {
    std::ifstream rating(rating_file);  //change this to test the full file
    if (not rating) {
        throw std::runtime_error("Incorrect rating.csv file");
    }
    std::string file_line{};
    std::getline(rating, file_line);  //get the first dumb line
    file_line.clear();
    while (std::getline(rating, file_line)) {
        int user_id{};
        int movie_id{};
        double movie_rating{};
        fill_rating_field(file_line, user_id, movie_id, movie_rating);
        movie_data.add_rating(movie_id, movie_rating);    //add the read rating on the hash
        ratings.insert(user_id, movie_id, movie_rating);  //add the new rating to the ordered array
    }
    rating.close();
}

void fill_rating_field(std::string& s, int& user_id, int& movie_id, double& rating) {
    int i{};
    std::string fields{};
    while (s[i] != ',') {
        fields += s[i];
        ++i;
    }
    user_id = std::stoi(fields);
    fields.clear();
    ++i;
    while (s[i] != ',') {
        fields += s[i];
        ++i;
    }
    movie_id = std::stoi(fields);
    fields.clear();
    ++i;
    while (s[i] != ',') {
        fields += s[i];
        ++i;
    }
    rating = std::stod(fields);
}

void Database::search_word(std::string& s) {
    movie_names.clear();
    movie_names.find(s);
    print_search(movie_names.infos());
}
void Database::print_search(std::vector<std::pair<std::string, unsigned>> vec) {
    using std::cout;
    using std::setw;
    std::cout.precision(6);
    std::cout << std::fixed;
    cout << setw(6) << "id"
         << "  " << setw(40) << std::right << "movie name" << setw(36) << "  " << std::right << "Genres"
         << "  " << setw(8) << "Rating"
         << "   " << setw(7) << "Count\n";
    //can i do this?
    std::sort(vec.begin(), vec.end(),
              [](const std::pair<std::string, unsigned>& a, const std::pair<std::string, unsigned>& b) {
                  return a.second < b.second;
              });
    for (auto& movie : vec) {
        auto current_movie_hash = movie_data.find(movie.second);
        cout << setw(6) << movie.second << "  "
             << setw(40) << std::right << string_print(movie.first) << "  ";
        std::string all_genres{};
        for (auto& genres : current_movie_hash.genres) {
            all_genres += genres;
            all_genres += "|";
        }
        auto grade{(current_movie_hash.all_ratings / current_movie_hash.number_of_ratings)};
        if (current_movie_hash.number_of_ratings == 0)
            grade = 0;
        cout << setw(40) << std::right << all_genres << "  ";
        cout << setw(7) << grade << "  " << setw(7) << current_movie_hash.number_of_ratings;
        cout << "\n";
    }
}

std::string string_print(const std::string& s) {
    if (s.size() < 40)
        return s;
    std::string new_s{};
    for (auto i{0U}; i < 37; ++i)
        new_s += s[i];
    new_s += "...";
    return new_s;
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