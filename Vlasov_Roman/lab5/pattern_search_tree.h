#ifndef PATTERN_SHEARCH_TREE_H
#define PATTERN_SHEARCH_TREE_H
#include <iostream>

#include <vector>
#include <string>
#include <queue>

class Pattern_Search_Tree
{
    typedef Pattern_Search_Tree PST;
    typedef Pattern_Search_Tree* PST_ptr;
private:
    std::vector<PST_ptr> next;
    PST_ptr prev;
    PST_ptr suffix;
    PST_ptr finish;
    PST_ptr root;
    PST_ptr self_reference;
    std::queue<PST_ptr> queue;
    std::vector<unsigned int> pattern_numbers;
    //unsigned int pattern_number; //for pattern end
    char name;

    void destroy()
    {
        for (auto el : next)
        {
            el->destroy();
            delete el;
        }
    }
    PST_ptr find_next(char name_to_go) const
    {
        for (auto el : next)
            if (el->name == name_to_go)
                return el;
        return nullptr;
    }
    PST_ptr find_suffix() const
    {
        if (self_reference == root || prev == root)
        {
            return root;
        }
        else
        {
            PST_ptr link = prev->suffix;
            link = link->find_next(name);
            if (link)
                return link;
            else
            {
                link = prev->suffix;
                while(link != root)
                {
                    link = link->suffix;
                    PST_ptr tmp = link->find_next(name);
                    if (tmp)
                        return tmp;
                }
            }
            return root;
        }
    }
    PST_ptr find_finish() const
    {
        if (self_reference == root)
        {
            return nullptr;
        }
        else
        {
            PST_ptr link = suffix;
            if (link == root)
            {
                link = prev->suffix;
                while(link != root)
                {
                    PST_ptr tmp;
                    if ((tmp = link->find_next(name)))
                        if (tmp->is_final())
                            return tmp;
                    link = link->suffix;

                }
                return nullptr;
            }
            else
            {
                if (link->is_final() != 0)
                    return link;
                else
                {                    
                    return link->finish;
                }
            }
        }
    }
    void visit_all(std::queue<PST_ptr> &q)
    {
        PST_ptr link;
        std::queue<PST_ptr> tmp;
        tmp.push(self_reference);
        while(!tmp.empty())
        {
            link = tmp.front();
            tmp.pop();
            q.push(link);
            for (auto el : link->next)
            {
                tmp.push(el);
            }
        }

    }
    void update_all_suffix_links()
    {
        std::queue<PST_ptr> q = queue;
        while(!q.empty())
        {
            PST_ptr link = q.front();
            q.pop();
            link->suffix = link->find_suffix();
        }
    }
    void update_all_finish_links()
    {
        std::queue<PST_ptr> q = queue;
        while(!q.empty())
        {
            PST_ptr link = q.front();
            q.pop();
            link->finish = link->find_finish();
        }
    }

public:
    Pattern_Search_Tree(char name = 0,  PST_ptr prev = nullptr, PST_ptr head = nullptr) : name(name)
    {
        this->prev = prev;
        suffix = head;
        finish = nullptr;
        self_reference = this;
        if (head)
            root = head;
        else
            root = self_reference;
        //pattern_number = 0;
    }
    ~Pattern_Search_Tree()
    {
        if (this == root)
            destroy();
    }
    char get_name() const
    {
        return name;
    }
    unsigned int is_final() const
    {
        return pattern_numbers.size();
    }
    std::vector<unsigned int> get_final_marks()
    {
        return pattern_numbers;
    }
    void add_pattern(std::string& pattern, unsigned int num)
    {
        if (pattern.size() == 0)
        {
            pattern_numbers.push_back(num);
            return;
        }
        char ch = pattern.front();
        pattern.erase(pattern.begin());
        for (auto el : next)
        {
            if (el->get_name() == ch)
            {
                el->add_pattern(pattern, num);
                return;
            }
        }
        next.push_back(new PST(ch, self_reference, root));
        next.back()->add_pattern(pattern, num);
        return;
    }
    std::vector<std::pair<size_t, unsigned int>> search(std::string& str)
    {
        visit_all(queue);
        update_all_suffix_links();
        update_all_finish_links();
        std::vector<std::pair<size_t, unsigned int>> answer;
        size_t position = 0;
        PST_ptr state = root;
        PST_ptr tmp;
        while (position != str.size())
        {
            tmp = state->find_next(str[position]);
            if (tmp)
            {
                state = tmp;
            }
            else
            {
                state = state->suffix;
                while (state->is_final() && !state->next.size())
                    state = state->suffix;
                tmp = state->find_next(str[position]);
                while ((tmp == nullptr) && (state != root))
                {
                    state = state->suffix;
                    tmp = state->find_next(str[position]);
                }
                if (tmp)
                    state = tmp;
                else
                {
                    state = root;
                    position++;
                    continue;
                }
            }
            if (state->is_final())
            {
                for (auto el : state->pattern_numbers)
                {
                    answer.push_back(std::make_pair(position, el));
                }

            }
            tmp = state->finish;
            while (tmp)
            {
                for (auto el : tmp->pattern_numbers)
                {
                    answer.push_back(std::make_pair(position, el));
                }
                //answer.push_back(std::make_pair(position, tmp->is_final()));
                tmp = tmp->finish;
            }
            position++;
        }
        return answer;
    }
};

#endif // PATTERN_SHEARCH_TREE_H
