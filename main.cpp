#include <iostream>
#include "movement_problem.h"
#include "agis.h"
#include <vector>

int main()
{
    agis<problem> solver;
    problem body[3];
    float goal[] = {0, -9};
    float origin[] = {0, 0};
    body[0] = problem(origin, 0, 2, 91);
    body[1] = problem(&body[0].current, 0, 3, 91);
    body[2] = problem(&body[1].current, 0, 1, 91);
    body[0].current.set_child(&body[1].current);
    body[1].current.set_child(&body[2].current);

    body[2].current.set_goal(goal);

    std::cout << body[0].heuristic(body[0].current) << std::endl;
    body[0].current = body[0].apply(1);
    body[0].current.propagate_change();
    std::cout << body[0].heuristic(body[0].current) << std::endl;

    // int rule;
    // for (int i = 0; i < 3; i++)
    // {
    //     rule = solver.sthc(body[i]);
    //     std::cout << "returned " << rule << " on " << i << std::endl;

    //     if (rule <= body[i].max_rule && rule > 0)
    //     {
    //         std::cout << "applicable " << rule << " on " << i << std::endl;
    //         body[i].current = body[i].apply(rule);
    //         body[i].current.propagate_change();
    //     }
    // }

    // std::cout << body[0].current.awx << std::endl;
    // std::cout << body[1].current.awx << std::endl;
    // std::cout << body[2].current.awx << std::endl;

    // return 0;
}