#pragma once
#include <vector>

template <typename T>
void shellsort_ciura_basic(std::vector<T> &vec)
{
    std::vector<long long> gap_list{1750, 701, 301, 132, 57, 23, 10, 4, 1}; //ciura's optimal list
    while (static_cast<long long>(vec.size()) >= gap_list.at(0))
    {
        int element = floor(gap_list.at(0) * 2.25);
        gap_list.insert(gap_list.begin(), element);
    }
    for (auto gap : gap_list)
    {
        for (long long i{static_cast<long long>(gap)}; i < static_cast<long long>(vec.size()); ++i) //cicyles the vector, starting at gap
        {
            long long j{};
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
    std::vector<long long> gap_list{1750, 701, 301, 132, 57, 23, 10, 4, 1}; //ciura's optimal list
    while (static_cast<long long>(vec.size()) >= gap_list.at(0))
    {
        int element = floor(gap_list.at(0) * 2.25);
        gap_list.insert(gap_list.begin(), element);
    }
    for (auto gap : gap_list)
    {
        for (long long i{static_cast<long long>(gap)}; i < static_cast<long long>(vec.size()); ++i) //cicyles the vector, starting at gap
        {
            long long j{};
            auto temp = vec.at(i);
            for (j = i; j >= gap and vec[j - gap].second > temp.second; j -= gap)
            {
                vec.at(j) = vec.at(j - gap);
            }
            vec.at(j) = temp;
        }
    }
}