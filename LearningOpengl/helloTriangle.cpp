///*
//	VertexArray的作用到底是什么？
//*/
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//#include<iostream>
//#include<cmath>
//
//
////顶点着色器
//const GLchar* vert_shaderinfo =
//"#version 440 core\n"
//"layout (location = 0) in vec3 vPosition;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);\n"
//"}\n\0";
//
//const GLchar *vert_shaderinfo1 =
//"#version 440 core\n"
//"layout(location = 0) in vec3 vPosition; \n"
//"layout(location = 1) in vec4 vColor; \n"
//"out vec4 color;\n"
//"void main()\n"
//"{ \n"
//"gl_Position = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);\n"
//"color = vec4(vColor.r, vColor.g, vColor.b, 1.0);\n"
//"}\n\0";
//
////固定颜色片元着色器
//const GLchar *frag_shaderinfo =
//"#version 440 core\n"
//"out vec4 outColor;\n"
//"void main(){\n"
//"outColor = vec4(1.0, 0.0, 1.0, 0.0);\n"
//"}\n\0";
//
////不同颜色的固定片元着色器
//const GLchar *frag_shaderinfo1 =
//"#version 440 core\n"
//"out vec4 outColor;\n"
//"void main()"
//"{\n"
//"outColor = vec4(0.0, 1.0, 10.0, 0.0);"
//"}";
//
////可变颜色片元着色器
//const GLchar *frag_shaderinfo2 =
//"#version 440 core\n"
//"out vec4 outColor; \n"
//"uniform vec4 uColor; \n"
//"void main()\n"
//"{\n"
//"outColor = uColor;\n"
//"}\0";
//
//
//const GLchar *frag_shaderinfo3 =
//"#version 440 core\n;"
//"in vec4 color;\n"
//"out vec4 outColor;"
//"void main()\n"
//"{\n"
//"outColor = color;\n"
//"}\0";
//
//GLuint indices[] =
//{
//	0, 1, 2,
//	1, 2, 3
//};
//
//GLfloat vertices[] =
//{
//	0.5f, 0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	-0.5f, -0.5f, 0.0f,
//};
//
//GLfloat vertices1[] =
//{
//	0.5f, -0.5f, 0.0f,
//	-0.5f, -0.5f, 0.0f,
//	-0.5f, 0.5f, 0.0f
//};
//
//GLfloat vertices2[] =
//{
//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
//};
//
//GLint loadShader(const GLchar *shaderinfo, GLenum shaderType)
//{
//	GLint shader;
//	shader = glCreateShader(shaderType);
//	glShaderSource(shader, 1, &shaderinfo, NULL);
//	glCompileShader(shader);
//	return shader;
//
//}
//
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//}
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//	
//	GLFWwindow* window;
//	window = glfwCreateWindow(800, 600, "hello Triangle", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cerr << "Fail to create the window" << std::endl;
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)
//	{
//		std::cerr << "Fail to init glew" << std::endl;
//		return -1;
//	}
//
//	int width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//	glViewport(0, 0, width, height);
//	
//
//	glfwSetKeyCallback(window, key_callback);
//	//GLint vertShader;
//	//GLint fragShader;
//	//GLint success;
//	//GLchar loginfo[512];
//
//	//vertShader = loadShader(vert_shaderinfo1, GL_VERTEX_SHADER);
//	//glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
//	//if (!success)
//	//{
//	//	glGetShaderInfoLog(vertShader, 512, NULL, loginfo);
//	//	std::cout << "Error in compling shader" << loginfo << std::endl;
//	//}
//
//	//fragShader = loadShader(frag_shaderinfo3, GL_FRAGMENT_SHADER);
//	//glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
//	//if (!success)
//	//{
//	//	glGetShaderInfoLog(fragShader, 512, NULL, loginfo);
//	//	std::cout << "Error in compling shader" << loginfo << std::endl;
//	//}
//
//	//GLint program;
//	//program = glCreateProgram();
//	//glAttachShader(program, vertShader);
//	//glAttachShader(program, fragShader);
//	//glLinkProgram(program);
//
//	//glGetProgramiv(program, GL_LINK_STATUS, &success);
//	//if (!success)
//	//{
//	//	glGetShaderInfoLog(program, 512, NULL, loginfo);
//	//	std::cout << "Error in linking program:" << loginfo << std::endl;
//	//}
//
//
//	//GLuint VBO,VAO,EBO;
//	//glGenBuffers(1, &VBO);
//	//glGenVertexArrays(1,&VAO);
//	//glGenBuffers(1, &EBO);
//	////设置顶点数组
//	//glBindVertexArray(VAO);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//
//
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), ((void*)(0)));
//	//glEnableVertexAttribArray(0);
//
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	//glEnableVertexAttribArray(1);
//	//
//	//glBindVertexArray(0);
//	//glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		////render
//
//		//glClear(GL_COLOR_BUFFER_BIT);
//		//glUseProgram(program);
//
//		////两个新的接口：glGetUniformLocation(program, "uColor"), glUniform4f(location, "uniform变量内部的数据");
//		//GLfloat time = glfwGetTime();
//		//GLfloat color = (sin(time) / 2) + 0.5;
//		//GLint colorLocation = glGetUniformLocation(program, "uColor");
//		//glUniform4f(colorLocation, 0.0, color, 0.0, 0.0);
//
//
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		glBindVertexArray(0);
//
//		glBindVertexArray(VAO);
//		//swap the buffeer
//		glfwSwapBuffers(window);
//	}
//	//glDeleteBuffers(1, &VBO);
//	//glDeleteVertexArrays(1, &VAO);
//	//glDeleteBuffers(1, &EBO);
//	glfwTerminate();
//	return 0;
//
//}
//
