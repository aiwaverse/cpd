#include <vector>

template <typename T>
void shellsort_ciura_basic(std::vector<T> &vec)
{
    std::vector<int> gap_list{1750, 701, 301, 132, 57, 23, 10, 4, 1}; //ciura's optimal list
    while (vec.size() >= gap_list.at(0))
    {
        int element = floor(gap_list.at(0) * 2.25);
        gap_list.insert(gap_list.begin(), element);
    }
    for (auto gap : gap_list)
    {
        for (auto i{gap}; i < vec.size(); ++i) //cicyles the vector, starting at gap
        {
            int j{};
            T temp = vec.at(i);
            for (j = i; j >= gap and vec[j - gap] > temp; j -= gap)
            {
                vec.at(j) = vec.at(j - gap);
            }
            vec.at(j) = temp;
        }
    }
}

template <typename T1, typename T2>
void shellsort_ciura_basic(std::vector<std::pair<T1,T2>> &vec)
{
    std::vector<int> gap_list{1750, 701, 301, 132, 57, 23, 10, 4, 1}; //ciura's optimal list
    while (vec.size() >= gap_list.at(0))
    {
        int element = floor(gap_list.at(0) * 2.25);
        gap_list.insert(gap_list.begin(), element);
    }
    for (auto gap : gap_list)
    {
        for (auto i{gap}; i < vec.size(); ++i) //cicyles the vector, starting at gap
        {
            int j{};
            auto temp = vec.at(i);
            for (j = i; j >= gap and vec[j - gap].second > temp.second; j -= gap)
            {
                vec.at(j) = vec.at(j - gap);
            }
            vec.at(j) = temp;
        }
    }
}