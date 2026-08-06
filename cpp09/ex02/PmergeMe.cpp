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

void print(std::deque<uint> &v)
{
    for (std::deque<uint>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << "  " << *it;
    std::cout << "\n";
}

static void createPair(deque_pair_t &v, deque_pair_t &list_pair)
{
    for (deque_pair_t::iterator it = v.begin(); it != v.end() && it + 1 != v.end() ; it += 2)
    {
        uint a = (*it).first;
        uint b = (*(it + 1)).first;
        pair_t p(std::max(a, b), std::min(a, b));
        list_pair.push_back(p);
    }
}

static void creatJacobsthal(std::deque<uint> &v, uint len)
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
static pair_t findPair(deque_pair_t &v, uint first)
{
    deque_pair_t::iterator it;
    for (it = v.begin(); (*it).first != first; ++it)
        ;
    pair_t pair(*it);
    v.erase(it);
    return pair;
}

static deque_pair_t::iterator changeSecondPair(deque_pair_t &dst_list, deque_pair_t &src_list, uint first_pair)
{
    deque_pair_t::iterator it ;
    it = std::lower_bound(dst_list.begin(), dst_list.end(), first_pair, CompareFirst());
    (*it).second = (findPair(src_list, first_pair)).second;
    return it;
}

static deque_pair_t::iterator addPair(deque_pair_t &dst_list, deque_pair_t &src_list, pair_t pair, bool change_second = false)
{
    deque_pair_t::iterator it_end;
    deque_pair_t::iterator it;
    if (change_second)
        it_end = changeSecondPair(dst_list, src_list, pair.first);
    else
        it_end = dst_list.end();
    it = std::lower_bound(dst_list.begin(), it_end, pair.second, CompareFirst());
    return dst_list.insert(it, findPair(src_list, pair.second));
}

static pair_t reversePair(pair_t &pair)
{
    uint tmp;
    tmp = pair.first;
    pair.first = pair.second;
    pair.second = tmp;
    return pair;
}

static void recursionMergeInsert(deque_pair_t &dst_list, deque_pair_t &src_list)
{
    deque_pair_t list_pair;

    createPair(src_list, list_pair);
    if (list_pair.size() > 1)
        recursionMergeInsert(dst_list, list_pair);
    else
    {
        addPair(dst_list, src_list, list_pair.front());
        addPair(dst_list, src_list, reversePair(list_pair.front()));
        if (src_list.size())
            addPair(dst_list, src_list, reversePair(src_list.front()));
        return ;
    }
    list_pair = dst_list;
    std::deque <uint> jacobsthal;
    creatJacobsthal(jacobsthal, list_pair.size());
    for (uint i = 0; i < list_pair.size(); i++)
        addPair(dst_list, src_list, list_pair[jacobsthal[i]], true);
    if (src_list.size())
        addPair(dst_list, src_list, reversePair(src_list.front()));
}

void mergeInsert(std::deque<uint> &list)
{
    // create a list of pair
    if (list.size() < 2)
        return ;
    deque_pair_t list_pair;
    deque_pair_t result;
    for (std::deque<uint>::iterator it = list.begin(); it != list.end(); ++it)
        list_pair.push_back(pair_t(*it, 0));
    recursionMergeInsert(result, list_pair);
    list.clear();
    for (deque_pair_t::iterator it = result.begin(); it != result.end(); ++it)
        list.push_back((*it).first);
}


void print(std::vector<uint> &v)
{
    for (std::vector<uint>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << "  " << *it;
    std::cout << "\n";
}

static void createPair(vect_pair_t &v, vect_pair_t &list_pair)
{
    for (vect_pair_t::iterator it = v.begin(); it != v.end() && it + 1 != v.end() ; it += 2)
    {
        uint a = (*it).first;
        uint b = (*(it + 1)).first;
        pair_t p(std::max(a, b), std::min(a, b));
        list_pair.push_back(p);
    }
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
static pair_t findPair(vect_pair_t &v, uint first)
{
    vect_pair_t::iterator it;
    for (it = v.begin(); (*it).first != first; ++it)
        ;
    pair_t pair(*it);
    v.erase(it);
    return pair;
}


static vect_pair_t::iterator changeSecondPair(vect_pair_t &dst_list, vect_pair_t &src_list, uint first_pair)
{
    vect_pair_t::iterator it ;
    it = std::lower_bound(dst_list.begin(), dst_list.end(), first_pair, CompareFirst());
    (*it).second = (findPair(src_list, first_pair)).second;
    return it;
}

static vect_pair_t::iterator addPair(vect_pair_t &dst_list, vect_pair_t &src_list, pair_t pair, bool change_second = false)
{
    vect_pair_t::iterator it_end;
    vect_pair_t::iterator it;
    if (change_second)
        it_end = changeSecondPair(dst_list, src_list, pair.first);
    else
        it_end = dst_list.end();
    it = std::lower_bound(dst_list.begin(), it_end, pair.second, CompareFirst());
    return dst_list.insert(it, findPair(src_list, pair.second));
}

static void recursionMergeInsert(vect_pair_t &dst_list, vect_pair_t &src_list)
{
    vect_pair_t list_pair;

    createPair(src_list, list_pair);
    if (list_pair.size() > 1)
        recursionMergeInsert(dst_list, list_pair);
    else
    {
        addPair(dst_list, src_list, list_pair.front());
        addPair(dst_list, src_list, reversePair(list_pair.front()));
        if (src_list.size())
            addPair(dst_list, src_list, reversePair(src_list.front()));
        return ;
    }
    list_pair = dst_list;
    std::vector <uint> jacobsthal;
    creatJacobsthal(jacobsthal, list_pair.size());
    for (uint i = 0; i < list_pair.size(); i++)
        addPair(dst_list, src_list, list_pair[jacobsthal[i]], true);
    if (src_list.size())
        addPair(dst_list, src_list, reversePair(src_list.front()));
}

void mergeInsert(std::vector<uint> &list)
{
    // create a list of pair
    if (list.size() < 2)
        return ;
    vect_pair_t list_pair;
    vect_pair_t result;
    for (std::vector<uint>::iterator it = list.begin(); it != list.end(); ++it)
        list_pair.push_back(pair_t(*it, 0));
    list.clear();
    list.reserve(list_pair.size());
    recursionMergeInsert(result, list_pair);
    vect_pair_t::iterator it;
    for (it = result.begin(); it != result.end(); ++it)
        list.push_back((*it).first);
}
