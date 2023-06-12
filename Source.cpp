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
void DrawTable(std::vector<glm::vec3> , glm::mat4 );
void onMouseMove(GLFWwindow* , double , double );
void onMouseButton(GLFWwindow* , int , int , int );
void onScroll(GLFWwindow* , double , double );
void onSpaceClick(GLFWwindow*, int, int, int, int);
void SetupTableRendering();
bool checkCollisions();
std::vector<glm::vec3> CreateTableModel();
vector<Load::Obj> objArray;

//Propriedades do Movimento da Bola
float moveSpeed = 1.0f;
float rotationSpeed = 1.0f;
float ballRadius = 1.0f;
float initialDirectionalPosition = 0.0f;
bool ballIsMoving = false;
bool fullStop = false;



//Propriedades da Mesa
float tableThickness = 3.0f;    // Valores posteriormente divididos por 2,
float tableWidth = 25.0f;        // sendo que os v�rtice mais longe um do outro s�o esse valor 
float tableLength = 50.0f;       // positivo e negativo
float heightOffset = 0.0f;

GLuint tableVBO, tableVAO;
int tableVerticesCount;


GLuint shaderProgram,
sPositions,
sNormals,
sTexcoords,
sTexture;

vector<glm::vec3> positions = {
	// First row
	glm::vec3(.0f, 2.5f, -12.0f),       //Ball1
	glm::vec3(-2.0f, 2.5f, 3.0f),       //Ball2
	glm::vec3(2.0f, 2.5f, 3.0f),        //Ball3
										
	// Second row						
	glm::vec3(-1.0f, 2.5f, 5.0f),       //Ball4
	glm::vec3(3.0f, 2.5f, 5.0f),        //Ball5
	glm::vec3(-3.0f, 2.5f, 7.0f),       //Ball6
	glm::vec3(1.0f, 2.5f, 7.0f),        //Ball7
										
	// Third row						
	glm::vec3(-2.0f, 2.5f, 9.0f),       //Ball8
	glm::vec3(0.0f, 2.5f, 9.0f),        //Ball9
	glm::vec3(4.0f, 2.5f, 9.0f),        //Ball10
										
	// Fourth row						
	glm::vec3(-1.5f, 2.5f, 11.0f),      //Ball11
	glm::vec3(2.5f, 2.5f, 11.0f),       //Ball12
	glm::vec3(-2.5f, 2.5f, 13.0f),      //Ball13
										
	// Fifth row						
	glm::vec3(-0.5f, 2.5f, 15.0f),      //Ball14
	glm::vec3(3.5f, 2.5f, 15.0f),       //Ball15
	//glm::vec3(1.5f, 1.0f, 17.0f)      //Ball
};

vector<glm::vec3> orientations = {
	// First row
	glm::vec3(0.0f, 0.0f, 0.0f),        //Ball1
	glm::vec3(-2.0f, 2.5f, 3.0f),       //Ball2
	glm::vec3(2.0f, 2.5f, 3.0f),        //Ball3

	// Second row						
	glm::vec3(-1.0f, 2.5f, 5.0f),       //Ball4
	glm::vec3(3.0f, 2.5f, 5.0f),        //Ball5
	glm::vec3(-3.0f, 2.5f, 7.0f),       //Ball6
	glm::vec3(1.0f, 2.5f, 7.0f),        //Ball7

	// Third row						
	glm::vec3(-2.0f, 2.5f, 9.0f),       //Ball8
	glm::vec3(0.0f, 2.5f, 9.0f),        //Ball9
	glm::vec3(4.0f, 2.5f, 9.0f),        //Ball10

	// Fourth row						
	glm::vec3(-1.5f, 2.5f, 11.0f),      //Ball11
	glm::vec3(2.5f, 2.5f, 11.0f),       //Ball12
	glm::vec3(-2.5f, 2.5f, 13.0f),      //Ball13

	// Fifth row						
	glm::vec3(-0.5f, 2.5f, 15.0f),      //Ball14
	glm::vec3(3.5f, 2.5f, 15.0f),       //Ball15
	//glm::vec3(1.5f, 1.0f, 17.0f)      //Ball
};

GLuint tableShader;


#define HEIGHT 1600 
#define WIDTH 900

//View Movemnt
glm::mat4 modelMatrix = glm::mat4(1.0f);
double lastMouseX = 0;
double lastMouseY = 0;
bool isMouseDragging = false;

// Zoom level
float zoomLevel = 1.0f;


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
	//glfwSetKeyCallback(window, lighting::OnKeyPressed);

	//Glew Init must be called only when context has been defined 


	// Set up mouse input callbacks
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetMouseButtonCallback(window, onMouseButton);
	glfwSetScrollCallback(window, onScroll);
	glfwSetKeyCallback(window, onSpaceClick);


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

	{
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
	}
	/*Load::Obj obj, obj1, obj2, obj3, obj4, obj5;
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

	objArray.push_back(obj);*/

	//Table
	SetupTableRendering();

	/*Load::Obj obj1;
	objArray.push_back(obj1);
	obj1.Read("poolballs/Ball2.obj");

	//lighting::Lights(&obj1);

	objArray.push_back(obj1);
	objArray.push_back(obj2);
	objArray.push_back(obj3);
	objArray.push_back(obj4);
	objArray.push_back(obj5);
	*/

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Criar a matriz MVP
		glm::mat4 zoomMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(zoomLevel));
		glm::mat4 mvp = camera->projection * camera->view * modelMatrix * zoomMatrix;

		//glDrawArrays(GL_TRIANGLES, 0, 3); // NO INDEX BUFFER
		//

		
		//obj.Draw(glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f), modelMatrix * zoomMatrix);
		//obj1.Draw(glm::vec3(-2.0f, 0.0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f), modelMatrix);
		
		

		//DrawTable(tableModel, mvp);
		glUseProgram(shaderProgram);
		int i = 0;
		for (auto& obj : objArray)
		{
			if (i == 0 && ballIsMoving) {

				std::cout << "Ball Is Moving" << endl;

				//Translação
				positions[i].x += 0;
				positions[i].z += moveSpeed;

				//Rotação
				orientations[i].x += rotationSpeed;

				//Check for collision.  -> A class ball está preparada para resolver isto, mas a interligação está a dar problemas
				ballIsMoving = checkCollisions();

			}
			obj.Draw(positions[i++], glm::vec3(0.0f), modelMatrix * zoomMatrix);

			
		}
		//obj1.Draw(glm::vec3(3.0f, 0.0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f));
		DrawTable(tableModel, mvp );

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

bool checkCollisions() {

	// Checkamos para as outras bolas

	for (int i = 1; i < objArray.size(); i++)
	{
		float distance = glm::distance(positions[0], positions[i]);

		if (distance < ballRadius * 2) //Supõe-se que as bolas tenham o mesmo raio
		{

			std::cout << "Ball Hit Ball" << endl;
			fullStop = true;
			return false;
		}
	}

	//Caso não colida com bolas, vamos checkar os limites da mesa

	if (positions[0].x - ballRadius < -tableWidth / 2 ||
		positions[0].x + ballRadius > tableWidth / 2 ||
		positions[0].z - ballRadius < -tableLength / 2 ||
		positions[0].z + ballRadius > tableLength /2) {

		// Colidiu com a borda

		std::cout << "Ball Hit Border" << endl;
		fullStop = true;
		return false;
	}

	// Sem Colisões
	return true;
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

	/*std::cout << "vPosition: " << sPositions << " " <<
		std::endl << "vTexture: " << sTexcoords << " " << std::endl << "vNormal: " << sNormals << " " << std::endl << "texture frag: " << sTexture << " " << std::endl;*/

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;
	}

	ShaderInfo tableShaders[] = {
	{ GL_VERTEX_SHADER,"TableShader.vert" },
	{ GL_FRAGMENT_SHADER, "TableShader.frag" },
	{ GL_NONE, NULL }   //GL_None marca o final da lista de shader info
	};

	//Shader ID
	tableShader = LoadShaders(tableShaders);

}

void onScroll(GLFWwindow* window, double xoffset, double yoffset) {
	// Update zoom level based on scroll offset
	float zoomAmount = 0.1f;
	zoomLevel += yoffset * zoomAmount;

	// Clamp zoom level to a sensible range if desired
	// zoomLevel = glm::clamp(zoomLevel, 0.1f, 10.0f);
}

// Callback function for mouse movement event
void onMouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (isMouseDragging) {
		// Calculate mouse movement
		double deltaX = xpos - lastMouseX;
		double deltaY = ypos - lastMouseY;

		// Apply rotation to the model matrix
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians((float)deltaX), glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians((float)deltaY), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = rotation * modelMatrix;

		// Update last mouse position
		lastMouseX = xpos;
		lastMouseY = ypos;
	}
}

void onSpaceClick(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (fullStop) return;
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		ballIsMoving = !ballIsMoving;
	}
	//ambiente 1
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		cout << "test" << endl;
		if (lighting::light[0]) lighting::light[0] = false;
		else lighting::light[0] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		if (lighting::light[1]) lighting::light[1] = false;
		else lighting::light[1] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		if (lighting::light[2]) lighting::light[2] = false;
		else lighting::light[2] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		if (lighting::light[3]) lighting::light[3] = false;
		else lighting::light[3] = true;
	}
}

// Callback function for mouse button event
void onMouseButton(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			isMouseDragging = true;
			glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
		}
		else if (action == GLFW_RELEASE) {
			isMouseDragging = false;
		}
	}
}

void SetupTableRendering() {

	// Create and bind the VAO
	glGenVertexArrays(1, &tableVAO);
	glBindVertexArray(tableVAO);

	// Create the VBO and upload the table model data
	glGenBuffers(1, &tableVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tableVBO);

	std::vector<glm::vec3> tableModel = CreateTableModel();
	tableVerticesCount = tableModel.size();

	glBufferData(GL_ARRAY_BUFFER, tableModel.size() * sizeof(glm::vec3), &tableModel[0], GL_STATIC_DRAW);

	// Specify the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
	glEnableVertexAttribArray(0);

	// Unbind the VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawTable(std::vector<glm::vec3> tableModel, glm::mat4 mvp) {           // Testar se conseguimos ter o m�todo de display legacy a funcionar simult�neamente com o modern OpenGL
	
	glUseProgram(tableShader);
	glBindVertexArray(tableVAO);
	glUniformMatrix4fv(glGetUniformLocation(tableShader, "mvp"), 1, false, glm::value_ptr(mvp));
	glDrawArrays(GL_QUADS, 0, tableModel.size());
	glUseProgram(0);
}

std::vector<glm::vec3> CreateTableModel() {

	float lWidth = tableWidth / 2;
	float lThickness = tableThickness / 2 + heightOffset;
	float lLength = tableLength / 2;

	std::vector<glm::vec3> tableModel = {       //6 face com 4 v�rices, para fazer um paralelepipedo

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

		// Lado de baixo 
		glm::vec3(-lWidth, -lThickness,  lLength),
		glm::vec3(-lWidth, -lThickness, -lLength),
		glm::vec3(lWidth, -lThickness, -lLength),
		glm::vec3(lWidth, -lThickness,  lLength)

	};

	return tableModel;
}