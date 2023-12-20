#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>


GLFWwindow* CreateWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return NULL;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return NULL;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << '\n';
		return NULL;
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	return window;
}

std::string readShaderCode(const char* fileName)
{
	std::ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}

bool checkStatus(
	GLuint objectId,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint compileStatus;
	objectPropertyGetterFunc(objectId, statusType, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		getInfoLogFunc(objectId, infoLogLength, &bufferSize, buffer);

		std::cout << buffer << '\n';

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderId)
{
	return checkStatus(
		shaderId,
		glGetShaderiv,
		glGetShaderInfoLog,
		GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programId)
{
	return checkStatus(
		programId,
		glGetProgramiv,
		glGetProgramInfoLog,
		GL_LINK_STATUS);
}

void InstallShaders()
{
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);


	const GLchar* adapter[1];
	std::string temp = readShaderCode("./res/shaders/Vertex.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertex_shader_id, 1, adapter, NULL);
	temp = readShaderCode("./res/shaders/Fragment.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragment_shader_id, 1, adapter, NULL);

	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	if (!checkShaderStatus(vertex_shader_id) || !checkShaderStatus(fragment_shader_id))
		return;

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertex_shader_id);
	glAttachShader(ProgramID, fragment_shader_id);
	glLinkProgram(ProgramID);

	if (!checkProgramStatus(ProgramID))
		return;

	glUseProgram(ProgramID);
}

void sendDataToOpenGL()
{
	GLfloat vertices[] =
	{
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Vertex 1 (X, Y, Z)
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 2 (X, Y, Z)
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Vertex 3 (X, Y, Z)
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Vertex 4 (X, Y, Z)
	};

	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(3 * sizeof(float)));

	GLushort indices[] = {0, 1, 2, 2, 3, 0};
	GLuint indexBufferId;
	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

int main(void)
{
	GLFWwindow* window = CreateWindow();
	if (window == NULL)
		return -1;

	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	InstallShaders();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
