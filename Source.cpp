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
float tableWidth = 2.5f;        // sendo que os v�rtice mais longe um do outro s�o esse valor 
float tableLength = 4.0f;       // positivo e negativo
float heightOffset = 0.0f;

GLuint shaderProgram,
sPositions,
sNormals,
sTexcoords,
sTexture;

std::vector<glm::vec3> _ballPositions = {
	glm::vec3(4.1f, 0.33f, 4.1f),        // bola 1
	glm::vec3(-4.1f, 0.33f, -4.1f),        // bola 2
	glm::vec3(-4.1f, 0.33f, 4.1f),        // bola 3
	glm::vec3(4.1f, 0.33f, -4.1f),        // bola 4
	glm::vec3(0.1f, 0.33f, -0.1f),        // bola 5
	glm::vec3(-2.3f, 0.33f, -2.3f),        // bola 6
	glm::vec3(-2.6f, 0.33f, -0.4f),        // bola 7
	glm::vec3(1.8f, 0.33f, 1.2f),        // bola 8
	glm::vec3(-4.8f, 0.33f, -2.2f),        // bola 9
	glm::vec3(2.3f, 0.33f, 2.7f),        // bola 10
	glm::vec3(-.2f, 0.33f, -2.8f),        // bola 11
	glm::vec3(4.1f, 0.33f, -2.1f),        // bola 12
	glm::vec3(-2.9f, 0.33f, 2.6f),        // bola 13
	glm::vec3(2.1f, 0.33f, 3.3f),        // bola 14
	glm::vec3(2.4f, 0.33f, -2.6f),        // bola 15
};

vector<glm::vec3> positions = {
	// First row
	glm::vec3(0.0f, 1.0f, 0.0f),        // Cue ball (white)
	glm::vec3(-2.0f, 1.0f, 3.0f),       // Ball 1 (yellow)
	glm::vec3(2.0f, 1.0f, 3.0f),        // Ball 2 (blue)

	// Second row
	glm::vec3(-1.0f, 1.0f, 5.0f),       // Ball 3 (red)
	glm::vec3(3.0f, 1.0f, 5.0f),        // Ball 4 (purple)
	glm::vec3(-3.0f, 1.0f, 7.0f),       // Ball 5 (orange)
	glm::vec3(1.0f, 1.0f, 7.0f),        // Ball 6 (green)

	// Third row
	glm::vec3(-2.0f, 1.0f, 9.0f),       // Ball 7 (maroon)
	glm::vec3(0.0f, 1.0f, 9.0f),        // Ball 8 (black)
	glm::vec3(4.0f, 1.0f, 9.0f),        // Ball 9 (yellow-striped)

	// Fourth row
	glm::vec3(-1.5f, 1.0f, 11.0f),      // Ball 10 (blue-striped)
	glm::vec3(2.5f, 1.0f, 11.0f),       // Ball 11 (red-striped)
	glm::vec3(-2.5f, 1.0f, 13.0f),      // Ball 12 (purple-striped)

	// Fifth row
	glm::vec3(-0.5f, 1.0f, 15.0f),      // Ball 13 (orange-striped)
	glm::vec3(3.5f, 1.0f, 15.0f),       // Ball 14 (green-striped)
	//glm::vec3(1.5f, 1.0f, 17.0f)        // Ball 15 (brown)
};

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

	glewInit();
	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}
	else cout << "Glew Initialized Successfully " << "\n GL Version: " << glGetString(GL_VERSION) << endl;

	init();
	glfwSetKeyCallback(window, lighting::OnKeyPressed);

	//Glew Init must be called only when context has been defined 


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

	/*{
		using namespace Load;

		int a = 0;
		for (string i : objFiles)
		{
			Load::Obj obj;
			obj.Read(i, sPositions, sNormals, sTexcoords, sTexture, shaderProgram, a++);
			obj.Send();
			lighting::Lights(&obj, shaderProgram);
			objArray.push_back(obj);
		}
	}*/
	Load::Obj obj, obj1, obj2, obj3, obj4, obj5;
	obj.Read("poolballs/Ball1.obj", sPositions, sNormals, sTexcoords, sTexture, shaderProgram, 0);
	obj1.Read("poolballs/Ball2.obj", sPositions, sNormals, sTexcoords, sTexture, shaderProgram, 1);
	obj2.Read("poolballs/Ball3.obj", sPositions, sNormals, sTexcoords, sTexture, shaderProgram, 2);
	obj3.Read("poolballs/Ball4.obj", sPositions, sNormals, sTexcoords, sTexture, shaderProgram, 3);
	obj4.Read("poolballs/Ball5.obj", sPositions, sNormals, sTexcoords, sTexture, shaderProgram, 4);
	obj5.Read("poolballs/Ball6.obj", sPositions, sNormals, sTexcoords, sTexture, shaderProgram, 5);

	obj.Send();
	obj1.Send();
	obj2.Send();
	obj3.Send();
	obj4.Send();
	obj5.Send();

	lighting::Lights(&obj, shaderProgram);
	lighting::Lights(&obj1, shaderProgram);
	lighting::Lights(&obj2, shaderProgram);
	lighting::Lights(&obj3, shaderProgram);
	lighting::Lights(&obj4, shaderProgram);
	lighting::Lights(&obj5, shaderProgram);

	objArray.push_back(obj);
	objArray.push_back(obj1);
	objArray.push_back(obj2);
	objArray.push_back(obj3);
	objArray.push_back(obj4);
	objArray.push_back(obj5);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Model matrix = identidade
		glm::mat4 model = glm::mat4(1.0f);

		//Criar a matriz MVP
		glm::mat4 mvp = camera->projection * camera->view * model;

		//glDrawArrays(GL_TRIANGLES, 0, 3); // NO INDEX BUFFER
		//
		//DrawTable(tableModel, mvp);
		int i =0;
		for (auto& obj : objArray)
		{
			obj.Draw(positions[i++], glm::vec3(0.0f, 0.0f, 0.0f));
		}
		//obj1.Draw(glm::vec3(3.0f, 0.0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f));

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
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	ShaderInfo shaders[] = {
	{ GL_VERTEX_SHADER,"VballShader.vert" },
	{ GL_FRAGMENT_SHADER, "FballShader.frag" },
	{ GL_NONE, NULL }   //GL_None marca o final da lista de shader info
	};

	//Shader ID
	shaderProgram = LoadShaders(shaders);

	glUseProgram(shaderProgram); // Associa este shader program ao corrent render state

	sPositions = glGetProgramResourceLocation(shaderProgram, GL_PROGRAM_INPUT, "vertexPosition");
	sNormals = glGetProgramResourceLocation(shaderProgram, GL_PROGRAM_INPUT, "vertexNormals");
	sTexcoords = glGetProgramResourceLocation(shaderProgram, GL_PROGRAM_INPUT, "texCoords");

	sTexture = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "texSampler");
	std::cout << sPositions << " " << std::endl << sNormals << " " << std::endl << sTexcoords << " " << std::endl;
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;
	}

}

void DrawTable(std::vector<glm::vec3> tableModel, glm::mat4 mvp) {           // Testar se conseguimos ter o m�todo de display legacy a funcionar simult�neamente com o modern OpenGL
	//cout << "oi";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertex_stream = static_cast<float*>(glm::value_ptr(tableModel.front()));

	//Desenhar a mesa 

	glBegin(GL_QUADS);

	//Selecionar a cor
	glColor3f(0.0f, 0.7f, 0.3f);

	for (int nv = 0; nv < 6 * 4 * 3; nv += 3) {

		glm::vec4 vertex = glm::vec4(vertex_stream[nv], vertex_stream[nv + 1], vertex_stream[nv + 2], 1.0f);
		// C�lculo das coordenadas de recorte
		glm::vec4 transformed_vertex = mvp * vertex;
		// Divis�o de Perspetiva
		glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
		// Desenho do v�rtice
		glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
	}
	glEnd();
}

std::vector<glm::vec3> CreateTableModel() {

	float lWidth = tableWidth / 2;
	float lThickness = tableThickness / 2 + heightOffset;
	float lLength = tableLength / 2;

	glm::vec3 point[6 * 4] = {       //6 face com 4 v�rices, para fazer um paralelepipedo

		// Frente
		glm::vec3(-lWidth, -lThickness,  lLength),
		glm::vec3(lWidth, -lThickness,  lLength),
		glm::vec3(lWidth,  lThickness,  lLength),
		glm::vec3(-lWidth,  lThickness,  lLength),
		// Tr�s
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
		// Lado de baixo (n�o tem necess�riamente que ser desenhado, uma vez que a c�mera n�o se move)
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