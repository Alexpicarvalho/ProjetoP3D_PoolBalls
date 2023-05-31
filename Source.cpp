
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

void init(void);
float* createVertexBuffer(void);
void displayLegacy(void);
void display(void);

//Properties
float angle = 0.0f;

int main() {

	if (!glfwInit()) return -1;
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/


	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	else cout << "Window is Working" << endl;
	glfwMakeContextCurrent(window);

	//Glew Init must be called only when context has been defined 

	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}
	else cout << "Glew Initialized Successfully " << "\n GL Version: " << glGetString(GL_VERSION) << endl;

	init();

	//Buffer Creation
	GLuint buffer;
	GLfloat vertexPosition[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexPosition, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);


		glDrawArrays(GL_TRIANGLES, 0, 3); // NO INDEX BUFFER
		//displayLegacy();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void init() {
	glViewport(0, 0, 800, 600);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//glewExperimental = GL_TRUE;
	//glewInit();
}

float* createVertexBuffer() {

}

void display() {

}


void displayLegacy() {

	//Apply Transformation Changes
	glLoadIdentity();
	// Translate to the center of the screen
	glTranslatef(0.0f, 0.0f, 0.0f);

	// Rotate around the Y-axis
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	//cout << "Drawing" << endl;

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.5f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.5f, -0.5f);

	glEnd();

	angle += 1.0f;
}