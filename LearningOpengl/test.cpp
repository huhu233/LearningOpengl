//#include<gl/glew.h>
//#include<GLFW/glfw3.h>
//#include<iostream>
//#include<SOIL/SOIL.h>
//#include"Shader.h"
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	int width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//	glViewport(0, 0, width, height);
//
//	glfwSetKeyCallback(window, key_callback);
//
//	GLfloat vertices[] =
//	{
//		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//		-0.5f, -0.5, 0.0f, 0.0f,1.0f, 0.0f,
//		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
//	};
//
//	GLuint VAO, VBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0));
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(0);
//
//	Shader ourShader("vShader.vs", "fShader.frag");
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();	
//
//		glClearColor(0.0, 1.0, 1.0, 0.0);
//		glClear(GL_COLOR_BUFFER_BIT);
//		ourShader.Use();
//
//		//GLfloat time = glfwGetTime();
//		//GLfloat addtion = sin(time) / 2;
//
//		//GLuint offsetId;
//		//offsetId = glGetUniformLocation(ourShader.Program, "offset");
//		//glUniform1f(offsetId, addtion);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glBindVertexArray(0);
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteBuffers(1, &VBO);
//	glDeleteVertexArrays(1, &VAO);
//	
//	glfwTerminate();
//	return 0;
//	
//}
//
//
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//}
//
