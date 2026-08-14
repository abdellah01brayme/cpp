#include "PmergeMe.hpp"

static bool checkArg(char *s)
{
    if (!s[0])
        return false;
    for (int i = 0; s[i]; i++)
        if (!isdigit(s[i]) && s[i] != ' ')
            return false;
    return true;
}

void parser(std::vector<uint> &v, char **av, int ac)
{
    if (ac < 2)
        throw std::invalid_argument("Error: No arguments provided.");
    for (int i = 1; i < ac; i++)
    {
        if (!checkArg(av[i]))
            throw std::invalid_argument("Error: Invalid argument.");
        std::stringstream ss(av[i]);
        long n;
        while (!ss.eof())
        {
            ss >> n;
            if (ss.fail())
                break;
            if (n < 0 || n > std::numeric_limits<uint>::max())
                throw std::runtime_error("Error: negative or to big number." );
            std::vector<uint>::iterator it = std::find(v.begin(), v.end(), n);
            if (it != v.end())
                throw std::runtime_error("Error: duplication of numbers." );
            v.push_back(n);
        }        
    }
    if (v.size() < 1)
        throw std::runtime_error("Error: no numbers provided." );
}

 pair_t reversePair(pair_t &pair)
{
    uint tmp;
    tmp = pair.first;
    pair.first = pair.second;
    pair.second = tmp;
    return pair;
}

void printnode(t_node *node)
{
    if (!node)
        std::cout << "NULL";
    else
        std::cout << "[" << node->bigest << " " << node->lowest << "]  ";
}
void print(vect_pair_t &v)
{
    for (vect_pair_t::iterator it = v.begin(); it != v.end(); ++it)
    {
        printnode(&(*it));
        std::cout << "-->  ";
        printnode((*it).lowest_node);
        std::cout << "\n";
    }
    std::cout << "\n========\n";
}

static void creatJacobsthal(std::vector<uint> &v, uint len)
{
    uint i;
    uint end = 1;
    uint j1 = 1, j2 = 1;
    v.push_back(0);
    v.push_back(1);
    for (i = 2; i < len; )
    {
        end = j1 * 2 + j2;
        if (end - j2 > len - i)
            end = j2 + len - i;
        for (uint tmp = end ; tmp > j2; tmp--, i++)
            v.push_back(tmp);
        j1 = j2;
        j2 = end;
    }
}

void createPair(vect_pair_t &list_pair, std::vector<uint> &list)
{
    for (std::vector<uint>::iterator it = list.begin(); it != list.end(); ++it)
        list_pair.push_back((node){*it, 0, NULL, NULL});
}

static void createPair(vect_pair_t &list_pair, vect_pair_t &v)
{
    t_node node;
    for (vect_pair_t::iterator it = v.begin(); it != v.end() && it + 1 != v.end() ; it += 2)
    {
        if ((*it).bigest > (*(it + 1)).bigest)
        {
            node.bigest = (*it).bigest;
            node.lowest = (*(it + 1)).bigest;
            node.bigest_node = &(*it);
            node.lowest_node = &(*(it + 1));
        }
        else
        {
            node.bigest = (*(it + 1)).bigest;
            node.lowest = (*it).bigest;
            node.bigest_node = &(*(it + 1)); 
            node.lowest_node = &(*it); 
        }
        list_pair.push_back(node);
    }
}

static vect_pair_t::iterator changeOrigine(vect_pair_t &dst_list, t_node node)
{
    vect_pair_t::iterator it ;
    it = std::lower_bound(dst_list.begin(), dst_list.end(), node.bigest, CompareFirst());
    if ((*it).bigest_node)
    {
        (*it).bigest = (*it).bigest_node->bigest;
        (*it).lowest = (*it).bigest_node->lowest;
        (*it).lowest_node = (*it).bigest_node->lowest_node;
        (*it).bigest_node = (*it).bigest_node->bigest_node;
    }
    return it;
}

static vect_pair_t::iterator addPair(vect_pair_t &dst_list, vect_pair_t::iterator it_end, t_node &node)
{
    vect_pair_t::iterator it;
    it = std::lower_bound(dst_list.begin(), it_end, node.bigest, CompareFirst());
    return dst_list.insert(it, node);
}

static void recursionMergeInsert(vect_pair_t &dst_list, vect_pair_t &src_list)
{
    vect_pair_t list_pair;

    createPair(list_pair, src_list);
    if (list_pair.size() > 1)
        recursionMergeInsert(dst_list, list_pair);
    else
    {
        dst_list.insert(dst_list.begin(), *list_pair.front().lowest_node);
        if (src_list.front().bigest == dst_list.front().bigest)
            dst_list.insert(dst_list.end(), *(src_list.begin() + 1));
        else
            dst_list.insert(dst_list.end(), src_list.front());
        if (src_list.size() > 2)
            addPair(dst_list, dst_list.end(), src_list.back());
        return ;
    }
    // print(dst_list);
    list_pair = dst_list;
    std::vector <uint> jacobsthal;
    creatJacobsthal(jacobsthal, list_pair.size());
    for (uint i = 0; i < list_pair.size(); i++)
    {
        vect_pair_t::iterator it_end = changeOrigine(dst_list, list_pair[jacobsthal[i]]);
        addPair(dst_list, it_end, *(list_pair[jacobsthal[i]].lowest_node));
    }
    if (src_list.size() > dst_list.size())
        addPair(dst_list, dst_list.end(), src_list.back());
}

void mergeInsert(std::vector<uint> &list)
{
    // create a list of pair
    if (list.size() < 2)
        return ;
    vect_pair_t list_pair;
    vect_pair_t result;
    createPair(list_pair, list);
    list.clear();
    list.reserve(list_pair.size());
    recursionMergeInsert(result, list_pair);
    vect_pair_t::iterator it;
    for (it = result.begin(); it != result.end(); ++it)
        list.push_back((*it).bigest);

}
