#include <iostream>
#include <algorithm>
#include <vector>
#include "pattern_search_tree.h"
#include <assert.h>
bool mycomp(const std::pair<size_t, unsigned int>& a, const std::pair<size_t, unsigned int>& b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}


int main()
{
    Pattern_Search_Tree tree;
    std::string str;
    std::string pattern;
    std::vector<size_t> pattern_sizes;
    std::cin >> str;
    /*
    std::cin >> n;
    for (unsigned int i = 1; i <= n; i++)
    {
        std::cin >> pattern;
        pattern_sizes.push_back(pattern.size());
        tree.add_pattern(pattern, i);
    }

    */
    std::cin >> pattern;
    char universal_symb;
    std::cin >> universal_symb;

    std::vector<size_t> C;
    std::vector<size_t> L;
    for (size_t i = 0; i <= pattern.size(); i++)
    {
        if ((i == pattern.size() || pattern[i] == universal_symb) && pattern[i-1] != universal_symb)
            L.push_back(i + 1);
    }
    C.push_back(L[0] == 1 ? 0 : 1);
    for (size_t i = 0; i < L.size() - 1; i++)
    {
        size_t t = L[i];
        while (pattern[t] == universal_symb)
        {
            t++;
        }
        C.push_back(t + 1);
    }

    for (unsigned int i = 1; i <= C.size(); i++)
    {
        std::string tmp;
        if (C[i-1] == 0)
        {
            pattern_sizes.push_back(0);
            continue;
        }
        for (size_t j = C[i-1]-1; j < L[i-1]-1; j++)
            tmp.push_back(pattern[j]);

        pattern_sizes.push_back(tmp.size());
        tree.add_pattern(tmp, i);
    }

    std::vector<std::pair<size_t, unsigned int>> ans = tree.search(str);
    for (size_t i = 0; i < ans.size(); i++)
        ans[i].first = ans[i].first - pattern_sizes[ans[i].second - 1] + 2;

    size_t *arr = new size_t[str.size()];
    for (size_t i = 0; i < str.size(); i++)
        arr[i] = C[0] == 0 ? 1 : 0;
    for (auto el : ans)
    {
        //std::cout << el.first - C[el.second - 1] << ' ' << str.size() << std::endl;
        //assert(el.first - C[el.second - 1] < str.size());
        //assert(el.first - C[el.second - 1] >= 0);

        if (el.first - C[el.second - 1] < str.size())
            arr[el.first - C[el.second - 1]] += 1;
    }
    for (size_t i = 0; i < str.size(); i++)
        if (i + pattern.size() <= str.size() && arr[i] == L.size())
            std::cout << i+1 << std::endl;


    /*
    std::sort(ans.begin(), ans.end(), mycomp);
    for (auto el : ans)
    {
        std::cout << el.first << ' ' << el.second << std::endl;
    }
    */
    delete[] arr;
    return 0;
}
