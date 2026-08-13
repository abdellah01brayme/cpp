#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    std::vector<uint> v;
    try
    {
        parser(v, av, ac);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    std::vector <uint> v2 = v;
    clock_t start = clock();
    mergeInsert(v);
    clock_t end = clock();
    clock_t starta = clock();
    std::sort(v2.begin(), v2.end());
    clock_t enda = clock();

    // 4. Calculate elapsed time
    double duration_sec = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    double duration_ms  = duration_sec * 1000000.0;
    double duration_us  = duration_sec * 1000.0;
    std::cout << "\ntime: \nms " << duration_ms << "\nus " << duration_us << std::endl;
    double duration_seca = static_cast<double>(enda - starta) / CLOCKS_PER_SEC;
    double duration_msa  = duration_seca * 1000000.0;
    double duration_usa  = duration_seca * 1000.0;
    std::cout << "\ntime: \nms " << duration_msa << "\nus " << duration_usa << std::endl;
    return 0;
}