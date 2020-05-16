#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>

namespace my_vector
{
    template <typename dtype>
    class my_vector
    {
    public:
        std::vector<dtype> v;
        bool exist()
        {
            if (this->v.size() > 0)
                return true;
            else
                return false;
        }
    };
} // namespace my_vector

class problem
{
public:
    const int max = 5;
    std::vector<std::vector<int>> map = std::vector<std::vector<int>>(max, std::vector<int>(max, 0));

    my_vector::my_vector<int> start;
    my_vector::my_vector<int> current;
    my_vector::my_vector<int> goal;
    int max_rule = 4;

    problem();
    ~problem() {}

    my_vector::my_vector<int> north();
    my_vector::my_vector<int> south();
    my_vector::my_vector<int> east();
    my_vector::my_vector<int> west();

    void dispaly();
    my_vector::my_vector<int> apply(int);
    float heuristic(my_vector::my_vector<int>);
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

problem::problem()
{
    int r;
    srand(time(0));
    start.v = std::vector<int>(2, 0);
    current.v = start.v;
    goal.v = std::vector<int>(2, max - 1);

    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < max; j++)
        {
            r = rand() % 10;

            if (r > 7)
                r = 1;
            else
                r = 0;

            map[i][j] = r;
        }
    }

    map[current.v[0]][current.v[1]] = 0;
    map[goal.v[0]][goal.v[1]] = 0;
}

my_vector::my_vector<int> problem::north()
{
    my_vector::my_vector<int> next;
    if (current.v[0] - 1 >= 0 && map[current.v[0] - 1][current.v[1]] != 1)
    {
        next.v.push_back(current.v[0] - 1);
        next.v.push_back(current.v[1]);
    }
    return next;
}

my_vector::my_vector<int> problem::south()
{
    my_vector::my_vector<int> next;
    if (current.v[0] + 1 < max && map[current.v[0] + 1][current.v[1]] != 1)
    {
        next.v.push_back(current.v[0] + 1);
        next.v.push_back(current.v[1]);
    }
    return next;
}
my_vector::my_vector<int> problem::east()
{
    my_vector::my_vector<int> next;
    if (current.v[1] + 1 < max && map[current.v[0]][current.v[1] + 1] != 1)
    {
        next.v.push_back(current.v[0]);
        next.v.push_back(current.v[1] + 1);
    }
    return next;
}
my_vector::my_vector<int> problem::west()
{
    my_vector::my_vector<int> next;
    if (current.v[1] - 1 >= 0 && map[current.v[0]][current.v[1] - 1] != 1)
    {
        next.v.push_back(current.v[0]);
        next.v.push_back(current.v[1] - 1);
    }
    return next;
}

void problem::dispaly()
{
    for (auto v : map)
    {
        for (auto value : v)
            std::cout << value;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

my_vector::my_vector<int> problem::apply(int rule)
{
    switch (rule)
    {
    case 1:
        return north();
    case 2:
        return south();
    case 3:
        return east();
    case 4:
        return west();
    default:
        return (my_vector::my_vector<int>());
    }
}

float problem::heuristic(my_vector::my_vector<int> next)
{
    return sqrt(pow(next.v[0] - goal.v[0], 2) + pow(next.v[1] - goal.v[1], 2));
}