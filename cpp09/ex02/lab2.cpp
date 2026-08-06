#include "PmergeMe.hpp"

bool checkArg(char *s)
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

void printPiar(std::vector<std::pair<uint, uint> > &pair)
{
    for (std::vector<std::pair<uint, uint> >::iterator it = pair.begin(); it != pair.end(); ++it)
        std::cout << "[ " << (*it).first << " , " << (*it).second << "], ";
    std::cout << std::endl;
}

void print(std::vector<uint> &v)
{
    for (std::vector<uint>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << "  " << *it;
    std::cout << "\n";
}

void createPair(std::vector<std::pair<uint, uint> > &v, std::vector<std::pair<uint, uint> > &list_pair)
{
    for (std::vector<std::pair<uint, uint> >::iterator it = v.begin(); it != v.end() && it + 1 != v.end(); it += 2)
    {
        uint a = (*it).first;
        uint b = (*(it + 1)).first;
        std::pair<uint, uint> p(std::max(a, b), std::min(a, b));
        list_pair.push_back(p);
    }
}

std::pair<uint, uint> findPair(std::vector<std::pair<uint, uint> > &v, uint first)
{
    std::vector<std::pair<uint, uint> >::iterator it;
    std::pair<uint, uint> pair;
    for (it = v.begin(); ; ++it)//(*it).first != first
    {
        pair = *it;
        if (pair.first != first)
            break;
    }
    pair = *it;
    // v.erase(it);
    return pair;
}

struct CompareFirst {
    bool operator()(const std::pair<uint, uint>& element, uint val) const {
        return element.first < val;
    }
};

std::vector<std::pair<uint, uint> >::iterator changeSecondPair(std::vector<std::pair<uint, uint> > &dst_list, std::vector<std::pair<uint, uint> > &src_list, uint first_pair)
{
    std::vector<std::pair<uint, uint> >::iterator it ;
    it = std::lower_bound(dst_list.begin(), dst_list.end(), first_pair, CompareFirst());
    (*it).second = findPair(src_list, first_pair).second;
    return it;
}

std::vector<std::pair<uint, uint> >::iterator addPair(std::vector<std::pair<uint, uint> > &dst_list, std::vector<std::pair<uint, uint> > &src_list, std::vector<std::pair<uint, uint> >::iterator it_start, std::pair<uint, uint> pair, bool change_second)
{
    std::vector<std::pair<uint, uint> >::iterator it_end;
    std::vector<std::pair<uint, uint> >::iterator it;
    if (change_second)
        it_end = changeSecondPair(dst_list, src_list, pair.first);
    else
        it_end = dst_list.end();
    it = std::lower_bound(it_start, it_end, pair.second, CompareFirst());
    it = dst_list.insert(it, findPair(src_list, pair.second));
    return it;
}
void creatJacobsthal(std::vector<uint> &v, uint len)
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
void recursionMergeInsert(std::vector<std::pair<uint, uint> > &dst_list, std::vector<std::pair<uint, uint> > &src_list)
{
    std::vector<std::pair<uint, uint> > tmp_list_pair;

    createPair(src_list, tmp_list_pair);
    if (tmp_list_pair.size() > 1)
        recursionMergeInsert(dst_list, tmp_list_pair);
    else
    {
        addPair(dst_list, src_list, dst_list.begin(), tmp_list_pair[0], 0);
        std::swap(tmp_list_pair.back().first, tmp_list_pair.back().second);
        addPair(dst_list, src_list, dst_list.begin(), tmp_list_pair[0], 0);
        if (src_list.size() > dst_list.size())
        {
            std::pair<uint, uint> pair = src_list.back();
            std::swap(pair.second, pair.first);
            addPair(dst_list, src_list, dst_list.begin(), pair, 0);
        }
        return ;
    }
    

    tmp_list_pair = dst_list;
    std::vector<std::pair<uint, uint> >::iterator it_start = dst_list.begin();
    std::vector <uint> jacobsthal;
    creatJacobsthal(jacobsthal, tmp_list_pair.size());
    for (uint i = 0; i < tmp_list_pair.size(); i++)
    {
        it_start = addPair(dst_list, src_list, it_start, tmp_list_pair[jacobsthal[i]], 1);
    }
    if (src_list.size() > dst_list.size())
    {
        std::pair<uint, uint> pair = src_list.back();
        std::swap(pair.second, pair.first);
        addPair(dst_list, src_list, dst_list.begin(), pair, 0);
    }
    // printPiar(dst_list);

}
void mergeInsert(std::vector<uint> &v)
{
    // create a list of pair
    if (v.size() < 2)
        return ;
    std::vector<std::pair<uint, uint> > v_pair;
    std::vector<std::pair<uint, uint> > result;
    for (std::vector<uint>::iterator it = v.begin(); it != v.end(); ++it)
        v_pair.push_back(std::pair<uint, uint>(*it, 0));
    v.clear();
    v.reserve(v_pair.size());
    recursionMergeInsert(result, v_pair);
    std::vector<std::pair<uint, uint> >::iterator it;
    for (it = result.begin(); it != result.end(); ++it)
    {
        std::cout << "  " << (*it).first;
        v.push_back((*it).first);
    }
    std::cout << "\n" ;
}
