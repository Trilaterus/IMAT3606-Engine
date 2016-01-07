#include "CPModel.h"

CPModel::CPModel()
{
	clock.restart();
}

void CPModel::draw(sf::RenderWindow& window) const
{
	// Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
	static const GLfloat cube[] =
	{
		// positions    // texture coordinates
		-20, -20, -20, 0, 0,
		-20, 20, -20, 1, 0,
		-20, -20, 20, 0, 1,
		-20, -20, 20, 0, 1,
		-20, 20, -20, 1, 0,
		-20, 20, 20, 1, 1,

		20, -20, -20, 0, 0,
		20, 20, -20, 1, 0,
		20, -20, 20, 0, 1,
		20, -20, 20, 0, 1,
		20, 20, -20, 1, 0,
		20, 20, 20, 1, 1,

		-20, -20, -20, 0, 0,
		20, -20, -20, 1, 0,
		-20, -20, 20, 0, 1,
		-20, -20, 20, 0, 1,
		20, -20, -20, 1, 0,
		20, -20, 20, 1, 1,

		-20, 20, -20, 0, 0,
		20, 20, -20, 1, 0,
		-20, 20, 20, 0, 1,
		-20, 20, 20, 0, 1,
		20, 20, -20, 1, 0,
		20, 20, 20, 1, 1,

		-20, -20, -20, 0, 0,
		20, -20, -20, 1, 0,
		-20, 20, -20, 0, 1,
		-20, 20, -20, 0, 1,
		20, -20, -20, 1, 0,
		20, 20, -20, 1, 1,

		-20, -20, 20, 0, 0,
		20, -20, 20, 1, 0,
		-20, 20, 20, 0, 1,
		-20, 20, 20, 0, 1,
		20, -20, 20, 1, 0,
		20, 20, 20, 1, 1
	};

	// Enable position and texture coordinates vertex components
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

	// Disable normal and color vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// Clear the depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);

	// We get the position of the mouse cursor, so that we can move the box accordingly
	float x = sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
	float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, -100.f);
	glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
	glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
	glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
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