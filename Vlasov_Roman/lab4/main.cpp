#include <iostream>
#include <vector>

std::vector<size_t> prefix_function(const std::string& p, const std::string& t)
{
    std::vector<size_t> pref_t(p.length());
    pref_t[0] = 0;
    size_t k = 0;
    for (size_t i = 1; i < p.length(); i++)
    {

        while (k > 0 && p[k] != p[i])
            k = pref_t[k-1];
        if (p[k] == p[i])
            k++;
        pref_t[i] = k;
    }

    std::vector<size_t> pref(t.length());
    k = (p[0] == t[0] ? 1 : 0);
    pref[0] = k;
    for (size_t i = 1; i < t.length(); i++)
    {

        while (k >= p.length() || (k > 0 && p[k] != t[i]))
            k = pref_t[k-1];
        if (p[k] == t[i])
            k++;
        pref[i] = k;
    }
    return pref;
}

void print_ans(size_t l, std::vector<size_t> pref)
{
    std::vector<size_t> a;
    for (size_t i = 0; i < pref.size(); i++)
    {
        if (pref[i] == l)
            a.push_back(i - l + 1);
    }
    if (a.size())
    {
        std::cout << a[0];
        for (size_t i = 1; i < a.size(); i++)
            std::cout << ',' << a[i];
    }
    else {
        std::cout << -1;
    }
}

int check_shift(const std::string& a, const std::string& b)
{
    bool check = true;
    if (a.length() != b.length())
        return -1;
    for (size_t  i = 0; i < a.length(); i++)
    {
        check = true;
        if (a[0] == b[i])
        {
            for (size_t j = 0; j < a.length(); j++)
            {
                if (a[j] != b[(i + j) % a.length()])
                {
                    check = false;
                    break;
                }
            }
            if (check)
                return (int)i;
        }
    }
    return -1;
}

int main()
{
    std::string P;
    std::string T;
    std::cin >> P;
    std::cin >> T;
    std::vector<size_t> pref = prefix_function(P, T);
    print_ans(P.length(), pref);
    std::cout << check_shift(T, P);

    return 0;
}
