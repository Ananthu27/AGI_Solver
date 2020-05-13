#include <iostream>
#include <vector>
#include <time.h>
// #include <limits>

using namespace std;

template <typename dtype>

class agis
{
public:
    agis() {}
    ~agis() {}

    int shc(dtype (*apply)(int), float (*heuristic)(dtype), int max_rule, dtype current, dtype goal)
    {
        int rule = -1;

        if (current.exist() && heuristic(current) != 0)
        {
            try
            {
                vector<int> rule_applied = vector<int>(max_rule, 0);
                int rand_rule = rand() % max_rule + 1;
                srand(time(0));
                for (int i = 1; i < max_rule; i++)
                {
                    while (rand_rule > 0 && rand_rule <= max_rule && rule_applied[rand_rule] == 1)
                        rand_rule = rand() % max_rule + 1;
                    rule_applied[rand_rule] = 1;

                    dtype next = apply(rand_rule);

                    if (next.exist() && heuristic(current) > heuristic(next))
                    {
                        rule = rand_rule;
                        break;
                    }
                }
            }
            catch (exception e)
            {
                cout << " exception in shc" << endl;
            }
        }

        return rule;
    }

    int sthc(dtype (*apply)(int), float (*heuristic)(dtype), int max_rule, dtype current, dtype goal)
    {
        int rule = -1;

        if (current.exist() && heuristic(current) != 0)
        {
            try
            {
                float min = heuristic(current);
                for (int r = 1; r <= max_rule; r++)
                {
                    dtype next = apply(r);
                    if (next.exist() && heuristic(next) < min)
                        rule = r;
                }
            }
            catch (exception e)
            {
                cout << "exception in sthc " << endl;
            }
        }

        return rule;
    }
};