#include <vector>
#include <time.h>
#include <iostream>
// #include <limits>

template <typename dtype>

class agis
{
public:
    agis() {}
    ~agis() {}

    int shc(dtype);
    int sthc(dtype);
    static void documentation()
    {
        std::cout << "---@ DOCUMENTATION @---" << std::endl;
        std::cout << std::endl;
        std::cout << " Declare the class object as 'agis<typename> object_name;' " << std::endl;
        std::cout << " The typename is the class name of the problem class.\n Further the problem class will be reffered to as 'dtype'." << std::endl;
        std::cout << std::endl;
        std::cout << " dtype's object must include states start, current and goal. " << std::endl;
        std::cout << " These state objects should have a function 'bool exist();' which is used to check wheater they are initialised." << std::endl;
        std::cout << " dtype must include a 'int max_rule; which is initialesed as the max no of rules that are applicable." << std::endl;
        std::cout << " dtype's membser fuctions should include :" << std::endl;
        std::cout << std::endl;
        std::cout << " \t state apply(int rule_number);" << std::endl;
        std::cout << " \t\t which returns a state object initialised if rules is applicable and exist returns true for the returned object" << std::endl;
        std::cout << " \t\t and state object returns false on exist if rule in not applicable " << std::endl;
        std::cout << " \t\t apply is basically a int rule swithcher , with rule_number <= max_rule" << std::endl;
        std::cout << std::endl;
        std::cout << " \t float heuristic(state object)" << std::endl;
        std::cout << " \t\t returns the float distance value of a prediction of how far\n \t\tthe state passed as parameter to the function is from the goal state" << std::endl;
        std::cout << std::endl;
        std::cout << "---@ DOCUMENTATION @---" << std::endl;
    }
};

template <typename dtype>

int agis<dtype>::shc(dtype obj)
{
    int rule = -1;

    if (obj.current.exist() && obj.heuristic(obj.current) != 0)
    {
        try
        {
            std::vector<int> rule_applied = std::vector<int>(obj.max_rule, 0);
            int rand_rule = rand() % obj.max_rule + 1;
            srand(time(0));
            for (int i = 1; i < obj.max_rule; i++)
            {
                while (rand_rule > 0 && rand_rule <= obj.max_rule && rule_applied[rand_rule] == 1)
                    rand_rule = rand() % obj.max_rule + 1;
                rule_applied[rand_rule] = 1;

                auto next = obj.apply(rand_rule);

                if (next.exist() && obj.heuristic(obj.current) > obj.heuristic(next))
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
        try
        {
            float min = object.heuristic(object.current);
            for (int r = 1; r <= object.max_rule; r++)
            {
                auto next = object.apply(r);
                if (next.exist() && object.heuristic(next) < min)
                    rule = r;
            }
        }
        catch (std::exception e)
        {
            std::cout << "exception in sthc " << std::endl;
        }
    }

    return rule;
}