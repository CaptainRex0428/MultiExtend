#include "Render.h"

#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>

#include <Math/Vertex.h>

#include <MultiExtend.h>

static unsigned int CompileShader(unsigned int type,const std::string & source)
{
	unsigned int id = glCreateShader(type);
	const char * src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char * message = (char * )malloc(length * sizeof(char));
		glGetShaderInfoLog(id,length,&length,message);
		
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
	}

	std::cout << "Shader compiled >> " << type << " : " << id << std::endl;

	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int VS = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int FS = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, VS);
	glAttachShader(program, FS);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(VS);
	glDeleteShader(FS);

	std::cout << "Shader program compiled >> " << program << std::endl;

	return program;
}

int render::Render(const Vertex* vertices, unsigned int size)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	/* Initialize GLEW library */
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;

	unsigned int buffer;
	glGenBuffers(1,&buffer); // integer here is a specific identifier of buffer
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertices,GL_STATIC_DRAW);// specify the data and specify how to call draw

	std::string vertexShader = 
		"#version 330 core\n"
		"\n"
		"uniform mat4 MVP;\n"
		"in vec4 vCol;\n"
		"in vec4 vPos;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = MVP * vPos;\n"
		"    color = vCol;"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"in vec4 color;\n"
		"out vec4 fragment;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    fragment = color;\n"
		"}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	// tell the layout of attributes
	// 第一个参数（index）指定了你在着色器中为顶点属性所设置的位置索引。
	// 它用于将 OpenGL 绑定的顶点属性数据与顶点着色器中的相应输入变量相匹配。
	const unsigned int vPos_Idx =  glGetAttribLocation(shader,"vPos");
	glEnableVertexAttribArray(vPos_Idx);
	glVertexAttribPointer(
		vPos_Idx,
		sizeof(render::Vector) / sizeof(float), 
		GL_FLOAT, GL_FALSE, 
		sizeof(render::Vertex), 
		(void*)offsetof(render::Vertex, pos));

	const unsigned int vColor_Idx = glGetAttribLocation(shader, "vCol");
	glEnableVertexAttribArray(vColor_Idx);
	glVertexAttribPointer(
		vColor_Idx,
		sizeof(render::Color) / sizeof(float),
		GL_FLOAT, GL_FALSE,
		sizeof(render::Vertex),
		(void*)offsetof(render::Vertex, color));

	const unsigned int MVP_Idx = glGetUniformLocation(shader, "MVP");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;

		/* Render here */
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4 m, p, mvp;
		mat4x4_identity(m);

		float a = (float)glfwGetTime();
		mat4x4_rotate_Z(m, m, a);

		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUniformMatrix4fv(MVP_Idx, 1, GL_FALSE, (const GLfloat*)&mvp);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteShader(shader);

	glfwTerminate();
	return 0;
}
