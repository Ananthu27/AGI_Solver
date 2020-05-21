#include <iostream>
#include <math.h>
#include "my_math.h"

class limb
{
public:
    double joint[2];
    double awx, length;
    double climit, aclimit;
    limb *parent_joint;
    limb *child_joint;
    double goal[2] = {-1, -1};

    limb();
    limb(double *joint, double awx, double length, double limit);
    limb(limb *parent_joint, double awx, double length, double limit);
    limb(const limb &obj);
    ~limb();

    bool exist();
    void set_child(limb *child_joint);
    void set_goal(double *g);
    void propagate_change();
    double heuristic();
    void display();
};

limb::limb()
{
    joint[0] = -1;
}

limb::limb(double *joint, double awx, double length, double limit)
{
    for (int i = 0; i < 2; i++)
        this->joint[i] = *(joint + i);
    this->awx = awx;
    this->length = length;
    this->child_joint = NULL;
    this->climit = awx - limit;
    this->aclimit = awx + limit;
}

limb::limb(limb *parent_joint, double awx, double length, double limit)
{
    this->joint[0] = (cos(rad((*parent_joint).awx)) * (*parent_joint).length) + (*parent_joint).joint[0];
    this->joint[1] = (sin(rad((*parent_joint).awx)) * (*parent_joint).length) + (*parent_joint).joint[1];
    this->awx = awx;
    this->length = length;
    this->child_joint = NULL;
    this->climit = awx - limit;
    this->aclimit = awx + limit;
}

limb::limb(const limb &obj)
{
    for (int i = 0; i < 2; i++)
        joint[i] = obj.joint[i];

    awx = obj.awx;
    length = obj.length;
    parent_joint = obj.parent_joint;
    child_joint = obj.child_joint;
    climit = obj.climit;
    aclimit = obj.aclimit;

    for (int i = 0; i < 2; i++)
        goal[i] = obj.goal[i];

    // if (child_joint != NULL)
    // {
    //     (*child_joint).joint[0] = (cos(rad(awx)) * length) + joint[0];
    //     (*child_joint).joint[1] = (sin(rad(awx)) * length) + joint[1];
    // }
}

limb::~limb() {}

bool limb::exist()
{
    return joint[0] != -1 ? true : false;
}

void limb::set_child(limb *child_joint)
{
    this->child_joint = child_joint;
}

void limb::set_goal(double *g)
{
    try
    {
        for (int i = 0; i < 2; i++)
            goal[i] = *(g + i);
    }
    catch (std::exception e)
    {
        std::cout << "Exception while setting goal" << std::endl;
    }
}

void limb::propagate_change()
{
    if (child_joint != NULL)
    {
        (*child_joint).joint[0] = cos(rad(awx)) * length + joint[0];
        (*child_joint).joint[1] = sin(rad(awx)) * length + joint[1];
        (*child_joint).propagate_change();
    }
}

double limb::heuristic()
{
    double d = -1;

    bool go_to_next = false;

    if (goal[0] == -1)
        go_to_next = true;

    if (!go_to_next)
    {
        double x = (cos(rad(awx)) * length) + joint[0];
        double y = (sin(rad(awx)) * length) + joint[1];
        // std::cout << "the tip at : " << x << "," << y << " : ";
        d = sqrt(pow(x - goal[0], 2) + pow(y - goal[1], 2));
    }

    else if (child_joint != NULL)
        d = (*child_joint).heuristic();

    return d;
}

void limb::display()
{
    std::cout << "joint : " << joint[0] << "," << joint[1] << std::endl;
    std::cout << "awx : " << awx << std::endl;
    std::cout << "length : " << length << std::endl;
    std::cout << "climit : " << climit << std::endl;
    std::cout << "aclimit : " << aclimit << std::endl;
    std::cout << "goal : " << goal[0] << "," << goal[1] << std::endl;
    std::cout << std::endl;
}

class problem
{
public:
    limb current;
    int max_rule = 2;

    problem();
    problem(double *joint, double awx, double length, double limit);
    problem(limb *parent_joint, double awx, double length, double limit);
    ~problem();

    limb rotate_c();
    limb rotate_ac();
    limb apply(int rule);
    double heuristic(limb object);
};

problem::problem() {}

problem::problem(double *joint, double awx, double length, double limit)
{
    current = limb(joint, awx, length, limit);
}

problem::problem(limb *parent_joint, double awx, double length, double limit)
{
    current = limb(parent_joint, awx, length, limit);
}

problem::~problem()
{
}

limb problem::rotate_c()
{
    limb result;
    if ((current.awx - 1) > current.climit)
    {
        // std::cout << " can be rotated clock wise" << std::endl;
        result = current;
        result.awx -= 1;
        result.propagate_change();
    }
    return result;
}

limb problem::rotate_ac()
{
    limb result;
    if ((current.awx + 1) < current.aclimit)
    {
        // std::cout << " can be rotated anit clock wise" << std::endl;
        result = current;
        result.awx += 1;
        result.propagate_change();
    }
    return result;
}

double problem::heuristic(limb object)
{
    return object.heuristic();
}

limb problem::apply(int rule)
{
    limb result;
    if (rule > 0 && rule <= max_rule)
    {
        switch (rule)
        {
        case 1:
            result = rotate_c();
            break;
        case 2:
            result = rotate_ac();
            break;
        }
    }
    return result;
}
