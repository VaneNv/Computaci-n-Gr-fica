//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>

//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>

//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
//Café
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
//Verde fuerte
static const char* fShaderVfuerte = "shaders/shaderVfuerte.frag";
//Azul
static const char* fShaderAzul = "shaders/shaderAzul.frag"; 
//Verde
static const char* fShaderVerde = "shaders/shaderVerde.frag";
//Rojo
static const char* fShaderRojo = "shaders/shaderRojo.frag";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{

	//Aisgnando los vértices de la letra "V"
	GLfloat vertices_letraV[]{
		//X		Y		Z		R		G		B
		0.3f,	0.7f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.5f,	0.3f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.5f,	0.5f,	0.0f,	0.5f,	0.2f,	0.5f,

		0.5f,	0.3f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.5f,	0.5f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.7f,	0.7f,	0.0f,	0.5f,	0.2f,	0.5f,

		0.5f,	0.5f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.6f,	0.7f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.7f,	0.7f,	0.0f,	0.5f,	0.2f,	0.5f,

		0.4f,	0.7f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.5f,	0.5f,	0.0f,	0.5f,	0.2f,	0.5f,
		0.3f,	0.7f,	0.0f,	0.5f,	0.2f,	0.5f,

	};

	MeshColor* letraV = new MeshColor();
	letraV->CreateMeshColor(vertices_letraV, 72);
	meshColorList.push_back(letraV);

	//Aisgnando los vértices de la letra "A"
	GLfloat vertices_letraA[]{
		//X		Y		Z		R		G		B
		-0.1f,	0.3f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.0f,	0.3f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.1f,	0.5f,	0.0f,	0.0f,	0.255f,	0.0f,

		-0.1f,	0.3f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.1f,	0.5f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.1f,	0.7f,	0.0f,	0.0f,	0.255f,	0.0f,

		0.1f,	0.7f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.1f,	0.5f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.3f,	0.3f,	0.0f,	0.0f,	0.255f,	0.0f,

		0.2f,	0.3f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.3f,	0.3f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.1f,	0.5f,	0.0f,	0.0f,	0.255f,	0.0f,

		0.05f,	0.4f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.0f,	0.35f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.18f,	0.4f,	0.0f,	0.0f,	0.255f,	0.0f,

		0.0f,	0.35f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.2f,	0.35f,	0.0f,	0.0f,	0.255f,	0.0f,
		0.18f,	0.4f,	0.0f,	0.0f,	0.255f,	0.0f,
	};

	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 108);
	meshColorList.push_back(letraA);
	 
	//Aisgnando los vértices de la letra "N"
	GLfloat vertices_letraN[]{
		//X		Y		Z		R		G		B
		-0.7f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.6f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.7f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,

		-0.7f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.6f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.6f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,
			
		-0.6f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.6f,	0.6f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.5f,	0.6f,	0.0f,	0.2f,	0.1f,	0.3f,

		-0.6f,	0.6f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.5f,	0.6f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.4f,	0.4f,	0.0f,	0.2f,	0.1f,	0.3f,

		-0.5f,	0.6f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.4f,	0.4f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.3f,	0.4f,	0.0f,	0.2f,	0.1f,	0.3f,

		-0.4f,	0.4f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.3f,	0.4f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.3f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,

		-0.3f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.3f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.2f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,

		-0.2f,	0.3f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.2f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,
		-0.3f,	0.7f,	0.0f,	0.2f,	0.1f,	0.3f,
	};

	MeshColor* letraN = new MeshColor();
	letraN->CreateMeshColor(vertices_letraN, 144);
	meshColorList.push_back(letraN);
}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	//Shader 1- Café
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//shader COLOR VERDE OSCURO
	Shader* shader3 = new Shader(); 
	shader3->CreateFromFiles(vShader, fShaderVfuerte);
	shaderList.push_back(*shader3);

	//shader COLOR VERDE 
	Shader* shader4 = new Shader(); 
	shader4->CreateFromFiles(vShader, fShaderVerde);
	shaderList.push_back(*shader4);

	//shader COLOR AZUL
	Shader* shader5 = new Shader(); 
	shader5->CreateFromFiles(vShader, fShaderAzul);
	shaderList.push_back(*shader5);

	//shader COLOR Rojo
	Shader* shader6 = new Shader(); 
	shader6->CreateFromFiles(vShader, fShaderRojo);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f); // radiasn es el FOV (punto de vista)
	
	//Para vista en 3D
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas

		// Letra V
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, 1.3f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		// Letra A
		model = glm::mat4 (1.0);
		model = glm::translate(model, glm::vec3(1.5f, 1.3f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		// Letra N
		model = glm::mat4 (1.0);
		model = glm::translate(model, glm::vec3(2.6f, 1.3f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		//Para la casa en 3D

		//Arboles
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Troncos
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(-2.5f, -1.1f, -5.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(2.5f, -1.1f, -5.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		//Hojas
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(-2.3f, -0.2f, -4.5f));
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(2.3f, -0.2f, -4.5f));
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Cubo rojo
		shaderList[5].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 0.5f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Triangulo azul
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, -4.5f));
		model = glm::scale(model, glm::vec3(2.7f, 1.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Ventanas 
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		//Ventana Izquierda
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(-0.6f, 0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Ventana derecha
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.6f, 0.4f, -4.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Puerta
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.5f)); 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/