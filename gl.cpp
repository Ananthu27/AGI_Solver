#include <GL/glut.h>
#include <iostream>
#include "movement_problem.h"
#include "agis.h"
#include "my_math.h"

agis<problem> solver;
problem body[2];

void init();
void display();
void reshape(int, int);
void timer(int);

int main(int i, char **c)
{
    glutInit(&i, c);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(900, 900);
    glutCreateWindow("main_window");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timer, 0);
    init();

    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(1, 1, 1, 1);

    float origin[] = {0, 0};
    body[0] = problem(origin, 0, 2, -91, 91);
    body[1] = problem(&body[0].current, 0, 2, -91, 91);
    body[0].current.set_child(&body[1].current);

    float goal[] = {0, 0};
    body[1].current.set_goal(goal);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0, 0, 0);

    glBegin(GL_LINE_STRIP);
    {
        for (auto l : body)
        {
            glVertex2f(l.current.joint[0], l.current.joint[1]);
            float x = cos(rad(l.current.awx)) * l.current.length + l.current.joint[0];
            float y = sin(rad(l.current.awx)) * l.current.length + l.current.joint[1];
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
    for (int i = 0; i < 2; i++)
    {
        rule = solver.sthc(body[i]);
        if (rule <= body[i].max_rule && rule > 0)
        {
            body[i].current = body[i].apply(rule);
        }
        else
            continue;
    }

    // std::cout << arm.current.awx << std::endl;
}