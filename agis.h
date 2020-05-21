#include <vector>
#include <time.h>
#include <iostream>
#include <math.h>
// #include <limits>

template <typename dtype>

class agis
{
public:
    agis() {}
    ~agis() {}

    int shc(dtype);
    int sthc(dtype);
    int sma(dtype, double);
};

template <typename dtype>

int agis<dtype>::shc(dtype object)
{
    int rule = -1;

    if (object.current.exist() && object.heuristic(object.current) != 0)
    {
        try
        {
            std::vector<int> rule_applied = std::vector<int>(object.max_rule, 0);
            int rand_rule = rand() % object.max_rule + 1;
            srand(time(0));
            for (int i = 1; i < object.max_rule; i++)
            {
                while (rand_rule > 0 && rand_rule <= object.max_rule && rule_applied[rand_rule] == 1)
                    rand_rule = rand() % object.max_rule + 1;
                rule_applied[rand_rule] = 1;

                auto next = object.apply(rand_rule);

                if (next.exist() && object.heuristic(object.current) > object.heuristic(next))
                {
                    rule = rand_rule;
                    break;
                }
            }
        }
        catch (std::exception e)
        {
            std::cout << " exception in shc" << std::endl;
        }
    }

    return rule;
}

template <typename dtype>

int agis<dtype>::sthc(dtype object)
{
    int rule = -1;

    if (object.current.exist() && object.heuristic(object.current) != 0)
    {
        // std::cout << "start if " << std::endl;
        try
        {
            // std::cout << "start try " << std::endl;

            double min = object.heuristic(object.current);
            // std::cout << "min : " << min << std::endl;
            for (int r = 1; r <= object.max_rule; r++)
            {
                auto next = object.apply(r);

                // std::cout << next.exist() << std::endl;

                if (next.exist() && object.heuristic(next) < min)
                    rule = r;
            }
            // std::cout << "end try " << std::endl;
        }
        catch (std::exception e)
        {
            std::cout << "exception in sthc " << std::endl;
        }
        // std::cout << "end if " << std::endl;
    }

    return rule;
}

template <typename dtype>

int agis<dtype>::sma(dtype object, double temperature)
{
    srand(time(0));
    int rule = -1;
    if (object.current.exist() && object.heuristic(object.current) != 0)
    {
        try
        {
            std::vector<int> rule_applied = std::vector<int>(object.max_rule, 0);
            int rand_rule, sum;
            auto next = object.apply(-1);

            while (!next.exist())
            {
                rand_rule = rand() % object.max_rule + 1;

                next = object.apply(rand_rule);

                if (!next.exist())
                    rule_applied[rand_rule - 1] = 1;
                sum = 0;
                for (auto value : rule_applied)
                    sum += value;

                if (sum == object.max_rule)
                    break;
            }

            if (next.exist())
            {
                double cur_energy = object.heuristic(object.current);
                double new_energy = object.heuristic(next);

                if (new_energy < cur_energy)
                    rule = rand_rule;

                else if (abs(log(temperature) + temperature * sin(temperature)) >= ((double)rand() / 100000000))
                    rule = rand_rule;

                else
                    rule = -1;
            }
        }
        catch (std::exception e)
        {
            std::cout << "Exception in sma." << std::endl;
        }
    }
    return rule;
}