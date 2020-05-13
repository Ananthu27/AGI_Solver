#include <iostream>

using namespace std;

template <typename dtype>

class test
{
public:
    dtype goal, current, next;

    test() {}
    test(dtype g, dtype c, dtype n)
    {
        goal = g;
        current = c;
        next = n;
    }
    ~test() {}

    void display()
    {
        cout << goal << endl;
        cout << current << endl;
        cout << next << endl;
    }
};
int main()
{
}