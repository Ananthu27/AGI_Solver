#include <vector>
#include <time.h>
#include <iostream>
// #include <limits>

using namespace std;

template <typename dtype>

class agis
{
public:
    agis() {}
    ~agis() {}

    static void documentation()
    {
    }

    int shc(dtype obj)
    {
        int rule = -1;

        if (obj.current.exist() && obj.heuristic(obj.current) != 0)
        {
            try
            {
                vector<int> rule_applied = vector<int>(obj.max_rule, 0);
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
            catch (exception e)
            {
                cout << " exception in shc" << endl;
            }
        }

        return rule;
    }

    int sthc(dtype object)
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
            catch (exception e)
            {
                cout << "exception in sthc " << endl;
            }
        }

        return rule;
    }
};