#include "agis.h"
#include <iostream>
#include "test_problem.h"

int main()
{
    problem p;
    agis<problem> solver;
    solver.documentation();

    p.dispaly();

    std::cout << solver.sthc(p) << std::endl;
    return 0;
}