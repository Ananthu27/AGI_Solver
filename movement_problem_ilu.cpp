#include <GL/glut.h>
#include <iostream>
#include "movement_problem.h"
#include "agis.h"
#include "my_math.h"

agis<problem> solver;
problem body[3];
double goal[] = {2, 2};

void init();
void display();
void reshape(int, int);
void timer(int);

int main(int i, char **c)
{
    glutInit(&i, c);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("main_window");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timer, 0);
    init();

    glutMainLoop();
}

void init()
{
    srand(time(0));
    glClearColor(1, 1, 1, 1);
    glEnable(GL_PROGRAM_POINT_SIZE);

    double origin[] = {0, 0};
    body[0] = problem(origin, 0, 4, 180);
    body[1] = problem(&body[0].current, 90, 4, 90);
    body[2] = problem(&body[1].current, 90, 1, 90);
    body[0].current.set_child(&body[1].current);
    body[1].current.set_child(&body[2].current);

    body[2].current.set_goal(goal);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glLineWidth(2);
    glPointSize(4);

    glBegin(GL_POINTS);
    {
        glColor3f(1, 0, 0);
        glPointSize((GLfloat)20);
        glVertex2f(goal[0], goal[1]);
    }
    glEnd();
    glColor3f(0, 0, 0);

    glBegin(GL_LINE_STRIP);
    {
        for (auto l : body)
        {
            glVertex2f(l.current.joint[0], l.current.joint[1]);
            double x = cos(rad(l.current.awx)) * l.current.length + l.current.joint[0];
            double y = sin(rad(l.current.awx)) * l.current.length + l.current.joint[1];
            glVertex2f(x, y);
        }
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();

    glutTimerFunc(1000 / 60, timer, 0);

    int rule;
    float t = 100;
    if (t >= 0 && body[0].heuristic(body[0].current) > 0.1)
    {
        for (int i = 2; i >= 0; i--)
        {
            rule = solver.sthc(body[i]);
            if (rule <= body[i].max_rule && rule > 0)
            {
                body[i].current = body[i].apply(rule);
            }
        }
    }
    else
    {

        goal[0] = (rand() % 5) + 2;
        goal[1] = (rand() % 5) + 2;
        body[2].current.set_goal(goal);
    }

    // std::cout << arm.current.awx << std::endl;
}