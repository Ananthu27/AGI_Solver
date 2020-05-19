#include <iostream>
#include "movement_problem.h"
#include "agis.h"

int main()
{
    agis<problem> solver;
    // joint, awx, length, joint_to, climit, aclimit;
    float origin[] = {0, 0};
    problem arm(origin, 0, 5, -90, 90);
    problem forearm(&arm.current, 0, 4, -45, 45);
    float goal[] = {4, 3};
    arm.current.set_child(&forearm.current);
    forearm.current.set_goal(goal);

    // arm.current.display();
    // forearm.current.display();

    std::cout << arm.heuristic(arm.current) << std::endl;
    std::cout << forearm.heuristic(forearm.current) << std::endl;

    arm.current = arm.rotate_c();
    // arm.current.display();

    std::cout << arm.heuristic(arm.current) << std::endl;
    std::cout << forearm.heuristic(forearm.current) << std::endl;

    arm.current = arm.rotate_ac();
    arm.current = arm.rotate_ac();
    arm.current.display();

    std::cout << arm.heuristic(arm.current) << std::endl;
    std::cout << forearm.heuristic(forearm.current) << std::endl;

    // std::cout << solver.shc(arm) << std::endl;
    // std::cout << solver.sthc(arm) << std::endl;
    // std::cout << solver.sma(arm, 1000) << std::endl;

    // std::cout << arm.heuristic(arm.current) << std::endl;
    // std::cout << arm.current.awx << std::endl;

    // limb next;
    // int rule = 0;
    // while (true)
    // {
    //     rule = solver.sthc(arm);
    //     if (!(rule <= arm.max_rule && rule > 0))
    //         break;
    //     else
    //     {
    //         std::cout << rule << std::endl;
    //         arm.current = arm.apply(rule);
    //     }
    // }

    // std::cout << arm.heuristic(arm.current) << std::endl;
    // std::cout << arm.current.awx << std::endl;

    return 0;
}