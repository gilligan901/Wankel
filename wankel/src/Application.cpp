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
		std::cout << "Error" << std::endl;
		return NULL;
	}

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

	GLint compileStatus;
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		glGetShaderInfoLog(vertex_shader_id, infoLogLength, &bufferSize, buffer);

		std::cout << buffer << '\n';

		delete[] buffer;
	}

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertex_shader_id);
	glAttachShader(ProgramID, fragment_shader_id);

	glLinkProgram(ProgramID);

	glDetachShader(ProgramID, vertex_shader_id);
	glDetachShader(ProgramID, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	glUseProgram(ProgramID);
}


int main(void)
{
	GLFWwindow* window = CreateWindow();
	if (window == NULL)
		return -1;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
