#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

struct edge{
    int max_bandwidth = 0;
    int final_bandwidth = 0;
    bool from_input = false;

    edge& operator= (const int b)
    {
        this->max_bandwidth = b;
        return *this;
    }
};

class graph
{
    char start;
    char finish;
    int max_flow;
    std::vector<char> indexes;
    edge** matrix;
    size_t reserved_indexes;

    size_t find_index(char name)
    {
        for (size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == name)
                return i;
        }

        if (indexes.size() == reserved_indexes)
            realloc();
        indexes.push_back(name);
        return indexes.size() - 1;
    }

    void realloc()
    {
        size_t res = reserved_indexes + 10;
        edge** tmp = new edge*[res];
        for (size_t i = 0; i < res; i++)
        {
            matrix[i] = new edge[res];
        }
        for (size_t i = 0; i < reserved_indexes; i++)
            for (size_t j = 0; j < reserved_indexes; j++)
            {
                tmp[i][j] = matrix[i][j];
            }
        clear_matrix();
        matrix = tmp;
        reserved_indexes = res;
    }

    void clear_matrix()
    {
        for (size_t i = 0; i < reserved_indexes; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    std::vector<char> find_path_dfs()
    {
        char current = start;
        std::vector<char> current_path;
        std::vector<char> visited = indexes;  // 0 - if visited
        std::stack<std::pair<char, std::vector<char>>> dfs_stack;
        dfs_stack.push(std::make_pair(current, current_path));
        visited[find_index(current)] = 0;

        while (!dfs_stack.empty())
        {
            current = dfs_stack.top().first;
            current_path = dfs_stack.top().second;
            dfs_stack.pop();
            current_path.push_back(current);
            size_t ind = find_index(current);
            for (size_t i = 0; i < indexes.size(); i++)
            {
                if (visited[i] && matrix[ind][i].max_bandwidth)
                {
                    if (indexes[i] == finish)
                    {
                        current_path.push_back(finish);
                        return current_path;
                    }

                    visited[i] = 0;
                    dfs_stack.push(std::make_pair(indexes[i], current_path));
                }
            }
        }
        return std::vector<char>();
    }

    int find_min_bandwidth(std::vector<char> path)
    {
        size_t ind_f, ind_d;
        ind_f = find_index(path[0]);
        ind_d = find_index(path[1]);
        int cur_min = matrix[ind_f][ind_d].max_bandwidth;

        for (size_t i = 2; i < path.size(); i++)
        {
            ind_f = ind_d;
            ind_d = find_index(path[i]);
            if (matrix[ind_f][ind_d].max_bandwidth < cur_min)
                cur_min = matrix[ind_f][ind_d].max_bandwidth;
        }
        return cur_min;
    }

    void reduce_max_bandwidth(std::vector<char> path, int value)
    {
        size_t ind_f, ind_d;
        ind_f = find_index(path[0]);
        ind_d = find_index(path[1]);
        matrix[ind_f][ind_d].max_bandwidth -= value;
        matrix[ind_f][ind_d].final_bandwidth += value;

        for (size_t i = 2; i < path.size(); i++)
        {
            ind_f = ind_d;
            ind_d = find_index(path[i]);
            matrix[ind_f][ind_d].max_bandwidth -= value;
            matrix[ind_f][ind_d].final_bandwidth += value;
        }
    }

public:
    graph(char start, char finish)
    {
        this->start = start;
        this->finish = finish;
        max_flow = 0;
        reserved_indexes = 10;
        matrix = new edge*[reserved_indexes];
        for (size_t i = 0; i < reserved_indexes; i++)
            matrix[i] = new edge[reserved_indexes];
    }

    ~graph()
    {
        clear_matrix();
    }

    void add_edge(char from, char dest, int bandwidth)
    {
        size_t index_f = find_index(from);
        size_t index_d = find_index(dest);
        matrix[index_f][index_d] = bandwidth;
        matrix[index_f][index_d].from_input = true;
    }

    int find_flow()
    {
        std::vector<char> path = find_path_dfs();
        int cur_bandwidth = 0;

        while(path.size())
        {
            cur_bandwidth = find_min_bandwidth(path);
            max_flow += cur_bandwidth;
            reduce_max_bandwidth(path, cur_bandwidth);
            path = find_path_dfs();
        }
        return  max_flow;
    }

    void print_answer()
    {
        size_t ind_f, ind_d;
        std::vector<char> order = indexes;
        std::sort(order.begin(), order.end());
        std::cout << max_flow << std::endl;
        for (size_t i = 0; i < indexes.size(); i++)
        {
            ind_f = find_index(order[i]);
            for (size_t j = 0; j < indexes.size(); j++)
            {
                ind_d = find_index(order[j]);
                if (matrix[ind_f][ind_d].from_input)
                    std::cout << indexes[ind_f] << ' ' << indexes[ind_d] << ' ' << matrix[ind_f][ind_d].final_bandwidth << std::endl;
            }
        }
    }
};

#endif // GRAPH_H
