#include "PmergeMe.hpp"
#include <ctime>

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
    clock_t start = clock();
    mergeInsert(v);

    // 2. Execute your algorithm

    // 3. Record end ticks
    clock_t end = clock();

    // 4. Calculate elapsed time
    double duration_sec = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    double duration_ms  = duration_sec * 1000.0;
    double duration_us  = duration_sec * 1000000.0;
    std::cout << "\ntime: \nms " << duration_ms << "\nus " << duration_us << std::endl;
    return 0;
}