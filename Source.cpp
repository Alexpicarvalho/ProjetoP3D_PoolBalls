#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
using namespace std;

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

#include <Windows.h>
#include <string>
#include <vector>

#include "Load.h"

void init(void);
void DrawTable();
std::vector<glm::vec3> CreateTableModel();

//Propriedades da Mesa
float tableThickness = 0.5f;    // Valores posteriormente divididos por 2,
float tableWidth = 1.0f;        // sendo que os vértice mais longe um do outro são esse valor 
float tableLength = 1.5f;       // positivo e negativo
float heightOffset = 0.0f;


//Properties
float angle = 0.0f;

int main() {

	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Window", NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	else cout << "Window is Working" << endl;

	glfwMakeContextCurrent(window);
	init();
	glewInit();

	//Glew Init must be called only when context has been defined 

	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}
	else cout << "Glew Initialized Successfully " << "\n GL Version: " << glGetString(GL_VERSION) << endl;

	vector<string> objFiles{
		"poolballs/Ball1.obj",
			"poolballs/Ball2.obj",
			"poolballs/Ball3.obj",
			"poolballs/Ball4.obj",
			"poolballs/Ball5.obj",
			"poolballs/Ball6.obj",
			"poolballs/Ball7.obj",
			"poolballs/Ball8.obj",
			"poolballs/Ball9.obj",
			"poolballs/Ball10.obj",
			"poolballs/Ball11.obj",
			"poolballs/Ball12.obj",
			"poolballs/Ball13.obj",
			"poolballs/Ball14.obj",
			"poolballs/Ball15.obj"
	};

	vector<string> textureFiles
	{
		"poolballs/PoolBalluv1.jpg",
			"poolballs/PoolBalluv2.jpg",
			"poolballs/PoolBalluv3.jpg",
			"poolballs/PoolBalluv4.jpg",
			"poolballs/PoolBalluv5.jpg",
			"poolballs/PoolBalluv6.jpg",
			"poolballs/PoolBalluv7.jpg",
			"poolballs/PoolBalluv8.jpg",
			"poolballs/PoolBalluv9.jpg",
			"poolballs/PoolBalluv10.jpg",
			"poolballs/PoolBalluv11.jpg",
			"poolballs/PoolBalluv12.jpg",
			"poolballs/PoolBalluv13.jpg",
			"poolballs/PoolBalluv14.jpg",
			"poolballs/PoolBalluv15.jpg"
	};

	{
		using namespace Load;
		vector<Obj> objArray;

		for (string i : objFiles)
		{


			cout << i << endl;
		}
		Obj obj;
		objArray.push_back(obj);
		obj.Read("poolballs/Ball1.obj");
		obj.Send();
	}


	while (!glfwWindowShouldClose(window))
	{
		
		//glDrawArrays(GL_TRIANGLES, 0, 3); // NO INDEX BUFFER
		DrawTable();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void init() {
	glClearColor(0.02f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
}

void DrawTable() {           // Testar se conseguimos ter o método de display legacy a funcionar simultâneamente com o modern OpenGL

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Criar o modelo
	std::vector<glm::vec3> tableModel = CreateTableModel();
	
	//Desenhar a mesa 

	glBegin(GL_QUADS);

	//Selecionar a cor
	glColor3f(0.0f, 0.7f, 0.3f);

	for (int i = 0; i < tableModel.size(); i++)
	{
		glm::vec3 v1 = tableModel[i];
		glm::vec3 v2 = tableModel[i + 1];
		glm::vec3 v3 = tableModel[i + 2];
		glm::vec3 v4 = tableModel[i + 3];

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		glVertex3f(v4.x, v4.y, v4.z);
	}
	glEnd();
}

std::vector<glm::vec3> CreateTableModel() {

	float lWidth = tableWidth / 2;
	float lThickness = tableThickness / 2 + heightOffset;
	float lLength = tableLength / 2;

	glm::vec3 point[6 * 4] = {       //6 face com 4 vérices, para fazer um paralelepipedo

		// Frente
		glm::vec3(-lWidth, -lThickness,  lLength),
		glm::vec3(lWidth, -lThickness,  lLength),
		glm::vec3(lWidth,  lThickness,  lLength),
		glm::vec3(-lWidth,  lThickness,  lLength),
		// Trás
		glm::vec3(-lWidth, -lThickness, -lLength),
		glm::vec3(-lWidth,  lThickness, -lLength),
		glm::vec3(lWidth,  lThickness, -lLength),
		glm::vec3(lWidth, -lThickness, -lLength),
		// Lado Esquerdo
		glm::vec3(-lWidth, -lThickness,  lLength),
		glm::vec3(-lWidth,  lThickness,  lLength),
		glm::vec3(-lWidth,  lThickness, -lLength),
		glm::vec3(-lWidth, -lThickness, -lLength),
		// Lado Direito
		glm::vec3(lWidth, -lThickness,  lLength),
		glm::vec3(lWidth, -lThickness, -lLength),
		glm::vec3(lWidth,  lThickness, -lLength),
		glm::vec3(lWidth,  lThickness,  lLength),
		// Lado de cima
		glm::vec3(-lWidth,  lThickness,  lLength),
		glm::vec3(lWidth,  lThickness,  lLength),
		glm::vec3(lWidth,  lThickness, -lLength),
		glm::vec3(-lWidth,  lThickness, -lLength),
		// Lado de baixo (não tem necessáriamente que ser desenhado, uma vez que a câmera não se move)
		glm::vec3(-lWidth, -lThickness,  lLength),
		glm::vec3(-lWidth, -lThickness, -lLength),
		glm::vec3(lWidth, -lThickness, -lLength),
		glm::vec3(lWidth, -lThickness,  lLength)
	};

	std::vector<glm::vec3> tableModel;

	for (auto i : point)
	{
		tableModel.push_back(i);
	}

	return tableModel;
}