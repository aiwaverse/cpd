#include "movies.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <limits>
#include <queue>
#include <thread>
#include "algo.hpp"

Database::Database(std::string file_name) {
    using namespace std::chrono;
    auto start{steady_clock::now()};  //steady clock is monotonic
    std::cout << "Starting trie construction:\n";
    read_movie_file();
    std::cout << "Trie finished construction\n";
    std::cout << "Starting hash construction:\n";
    std::thread rating_thread(&Database::read_ratings_file, this, file_name);
    std::cout << "Starting tag hash construction:\n";
    //std::thread tags_thread(&Database::read_tags_file, this);
    read_tags_file();
    rating_thread.join();  //join the threads, wait for everything to finish
    //tags_thread.join();
    std::cout << "Hash finished construction\n";
    std::cout << "Ended tag hash construction\n";
    auto end{steady_clock::now()};
    auto time{duration_cast<nanoseconds>(end - start).count()};
    std::cout << "it all took " << time / 1000000000.0 << " seconds\n";
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

void Database::read_tags_file(void) {
    std::ifstream tags("Dados/tag.csv");
    if (not tags) {
        throw std::runtime_error("wrong tag.csv file");
    }
    std::string line{};
    std::getline(tags, line);  //get the fields line
    while (std::getline(tags, line)) {
        std::istringstream iss{line};
        std::string token{};
        std::getline(iss, token, ',');
        std::getline(iss, token, ',');
        int movie_id{std::stoi(token)};
        std::string tag = iss.str();
        tag = parse_quoted_line(tag);
        tag = trie::transform_string(tag);
        movie_tags.insert(tag, movie_id);
    }
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

void Database::search_user(unsigned id) {
    using std::left;
    using std::right;
    using std::setw;
    auto find_result{ratings.find(id)};
    std::cout << setw(11) << "user_rating"
              << "   " << setw(42) << "movie names   " << setw(12) << "global rating"
              << "   " << setw(4) << "count\n";
    for (auto entry : find_result.movie_ratings) {
        auto movie{movie_data.find(entry.first)};
        std::cout.precision(1);
        std::cout << std::fixed;
        std::cout << setw(11) << entry.second << "  " << setw(40) << string_print(movie.name) << "  ";
        auto grade{movie.all_ratings / movie.number_of_ratings};
        if (movie.number_of_ratings == 0)
            grade = 0;
        std::cout.precision(6);
        std::cout << std::fixed << setw(13) << grade << "  " << setw(7) << movie.number_of_ratings << "\n";
    }
}

void Database::search_top(const std::string& genre, unsigned n) {
    std::priority_queue<std::pair<double, unsigned>> top_movies{};
    for (unsigned i{}; i < 131262; ++i) {
        auto curr_movie = movie_data.find(i);
        std::string temp{};
        for (auto each : curr_movie.genres)
            temp += (each) + " ";
        std::string genres_low{};
        std::transform(temp.begin(), temp.end(), std::back_inserter(genres_low), ::tolower);
        if ((curr_movie.number_of_ratings >= 20) and (genres_low.find(genre) != std::string::npos)) {
            auto curr_grade = curr_movie.all_ratings / curr_movie.number_of_ratings;
            top_movies.push(std::make_pair(curr_grade, i));
        }
    }
    int i{};
    std::vector<unsigned> movies_to_send{};
    while (not top_movies.empty() and i < n) {
        movies_to_send.push_back(top_movies.top().second);
        top_movies.pop();
        ++i;
    }
    print_search(movies_to_send);
}

void Database::print_search(std::vector<std::pair<std::string, unsigned>> vec) {
    using std::cout;
    using std::setw;
    std::cout.precision(6);
    std::cout << std::fixed;
    cout << setw(8) << "id"
         << " " << setw(44) << std::right << "movie name"
         << "  " << setw(58) << std::right << "Genres"
         << " " << setw(9) << "Rating"
         << " " << setw(10) << "Count\n";
    //can i do this?
    /*std::sort(vec.begin(), vec.end(),
              [](const std::pair<std::string, unsigned>& a, const std::pair<std::string, unsigned>& b) {
                  return a.second < b.second;
              });*/
    shellsort_ciura_basic(vec);
    for (auto& movie : vec) {
        auto current_movie_hash = movie_data.find(movie.second);
        cout << setw(8) << movie.second
             << setw(45) << std::right << string_print(movie.first);
        std::string all_genres{};
        for (auto& genres : current_movie_hash.genres) {
            all_genres += genres;
            all_genres += "|";
        }
        auto grade{(current_movie_hash.all_ratings / current_movie_hash.number_of_ratings)};
        if (current_movie_hash.number_of_ratings == 0)
            grade = 0;
        cout << setw(60) << std::right << all_genres;
        cout << setw(10) << grade << setw(10) << current_movie_hash.number_of_ratings;
        cout << "\n";
    }
}

void Database::print_search(const std::vector<unsigned>& movies) {
    using std::setw;
    std::cout.precision(6);
    std::cout << std::fixed;
    std::cout << "   ";
    std::cout << setw(40) << "Movie name"
              << "  " << setw(70) << "Genres"
              << "  "
              << setw(8) << "Rating"
              << "  " << setw(8) << "Count\n";
    for (auto& m : movies) {
        auto curr{movie_data.find(m)};
        std::cout << "   " << setw(40) << string_print(curr.name) << "  ";
        std::string all_genres{};
        for (auto& g : curr.genres) {
            all_genres += g;
            all_genres += "|";
        }
        auto grade{(curr.all_ratings / curr.number_of_ratings)};
        if (curr.number_of_ratings == 0)
            grade = 0;
        std::cout << setw(70) << all_genres << "  " << setw(7) << grade << "  " << setw(7) << curr.number_of_ratings << "\n";
    }
}

void Database::search_tag(const std::vector<std::string>& tags) {
    //get the first set of tags and sort them
    auto m1 = movie_tags.find(tags.at(0));
    shellsort_ciura_basic(m1);
    std::vector<unsigned> m2{};
    for (unsigned i{1}; i < tags.size(); ++i) {
        //gets a new set of tags, sort them, and finds the insersection with the current tag set
        auto m3 = movie_tags.find(tags.at(i));
        shellsort_ciura_basic(m3);
        std::set_intersection(m1.begin(), m1.end(), m3.begin(), m3.end(), std::back_inserter(m2));
        //put the new tag set as m1, to use with the insersection again, as m1 gathers the full intersection
        m2.swap(m1);
        m2.clear();
    }
    print_search(m1);
}

std::string string_print(std::string& s) {
    if (*(s.end() - 1) == ' ')
        s.pop_back();
    if (s.size() < 40)
        return s;
    std::string new_s{};
    for (auto i{0U}; i < 37; ++i)
        new_s += s[i];
    new_s += "...";
    return new_s;
}

std::string parse_line(const std::string& s, unsigned info) {
    //in the end this is only used once, because it's innefficient to do regularly, aside from not working with sensitive strings
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
    auto i{first + 2};
    std::string new_s{};
    while ((i < s.size()) and ((s[i] != '\"') or (s[i+1] != ','))){
        new_s.push_back(s[i]);
        ++i;
    }
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
    if ((s == "(no genres listed)") or (s == "(no")){
        svec.push_back("(no genres listed)");
        return svec;
        }
    while (std::getline(iss, part, '|')) {
        svec.push_back(part);
    }
    return svec;
}
