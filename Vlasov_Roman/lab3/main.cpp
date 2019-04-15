#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    int n;
    std::cin >> n;
    char start, finish;
    std::cin >> start >> finish;
    graph gr(start, finish);
    for (int i = 0; i < n; i++)
    {
        int l;
        std::cin >> start >> finish >> l;
        gr.add_edge(start, finish, l);
    }
    gr.find_flow();
    gr.print_answer();

    return 0;
}
