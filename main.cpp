#include <iostream>
#include "movement_problem.h"
#include "agis.h"
#include <vector>

int main()
{
    agis<problem> solver;
    problem body[2];
    float origin[] = {0, 0};
    body[0] = problem(origin, 0, 3, -90, 90);
    body[1] = problem(&body[0].current, 0, 4, -90, 90);
    body[0].current.set_child(&body[1].current);
    float goal[] = {0, 7};
    body[1].current.set_goal(goal);

    // for (auto l : body)
    //     l.current.display();
    std::cout << body[0].heuristic(body[0].current) << std::endl;

    int rule;
    bool bflag = false;
    while (!bflag)
    {
        for (int i = 0; i < 2; i++)
        {
            rule = solver.sthc(body[i]);
            if (rule <= body[i].max_rule && rule > 0)
            {
                body[i].current = body[i].apply(rule);
            }
            else
                bflag = true;
        }
    }

    std::cout << body[0].heuristic(body[0].current) << std::endl;

    return 0;
}