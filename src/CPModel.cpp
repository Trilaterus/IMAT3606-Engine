#include "CPModel.h"

CPModel::CPModel()
{

}


/* draw code for rotating coloured triangle
float ratio;
int width, height;
glfwGetFramebufferSize(window->getGLFWWindow(), &width, &height);
ratio = width / (float)height;

glViewport(0, 0, width, height);
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
glBegin(GL_TRIANGLES);
glColor3f(1.f, 0.f, 0.f);
glVertex3f(-0.6f, -0.4f, 0.f);
glColor3f(0.f, 1.f, 0.f);
glVertex3f(0.6f, -0.4f, 0.f);
glColor3f(0.f, 0.f, 1.f);
glVertex3f(0.f, 0.6f, 0.f);
glEnd();
*/