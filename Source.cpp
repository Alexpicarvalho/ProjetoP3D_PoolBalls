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
#include "Camera.h"
#include "Light.h"

void init(void);
void DrawTable(std::vector<glm::vec3> tableModel, glm::mat4 mvp);
std::vector<glm::vec3> CreateTableModel();
vector<Load::Obj> objArray;
//Propriedades da Mesa
float tableThickness = 0.25f;    // Valores posteriormente divididos por 2,
float tableWidth = 2.5f;        // sendo que os vértice mais longe um do outro são esse valor 
float tableLength = 4.0f;       // positivo e negativo
float heightOffset = 0.0f;


#define HEIGHT 1600
#define WIDTH 900
//Properties
float angle = 0.0f;

int main() {

	if (!glfwInit()) return -1;

	cam::Camera* camera;
	camera = camera->GetInstance();

	//Criar o modelo
	std::vector<glm::vec3> tableModel = CreateTableModel();


	GLFWwindow* window = glfwCreateWindow(1600, 900, "Window", NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	else cout << "Window is Working" << endl;

	glfwMakeContextCurrent(window);
	init();
	glewInit();
	glfwSetKeyCallback(window, lighting::OnKeyPressed);

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
		

		for (string i : objFiles)
		{
			cout << i << endl;
		}
	}
		Load::Obj obj;
		objArray.push_back(obj);
		obj.Read("poolballs/Ball1.obj");
		//obj.Send();


	while (!glfwWindowShouldClose(window))
	{
		//Model matrix = identidade
		glm::mat4 model = glm::mat4(1.0f);

		//Criar a matriz MVP
		glm::mat4 mvp = camera->projection * camera->view * model;

		//glDrawArrays(GL_TRIANGLES, 0, 3); // NO INDEX BUFFER
		DrawTable(tableModel, mvp);
		//for (auto obj : objArray)
		//{
			lighting::Lights(&obj);
			obj.Draw(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//}
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

void DrawTable(std::vector<glm::vec3> tableModel, glm :: mat4 mvp) {           // Testar se conseguimos ter o método de display legacy a funcionar simultâneamente com o modern OpenGL
	cout << "oi";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertex_stream = static_cast<float*>(glm::value_ptr(tableModel.front()));
	
	//Desenhar a mesa 

	glBegin(GL_QUADS);

	//Selecionar a cor
	glColor3f(0.0f, 0.7f, 0.3f);

	for (int nv = 0; nv < 6 * 4 * 3; nv += 3) {

		glm::vec4 vertex = glm::vec4(vertex_stream[nv], vertex_stream[nv + 1], vertex_stream[nv + 2], 1.0f);
		// Cálculo das coordenadas de recorte
		glm::vec4 transformed_vertex = mvp * vertex;
		// Divisão de Perspetiva
		glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
		// Desenho do vértice
		glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
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