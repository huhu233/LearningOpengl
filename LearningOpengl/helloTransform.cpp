///*
//	为何索引绘制只能绘制两个面
//*/
//#include<gl/glew.h>
//#include<GLFW/glfw3.h>
//#include<iostream>
//#include<SOIL/SOIL.h>
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
//#include"Shader.h"
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
//GLfloat mixParameter = 1;
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow *window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
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
//	int width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//	glViewport(0, 0, width, height);
//	glfwSetKeyCallback(window, key_callback);
//
//	//
//	//GLfloat vertices[] = {
//	//	// Positions          // Colors           // Texture Coords
//	//	0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//	//	0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//	//	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//	//	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top Left 
//
//	//	0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//	//	0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//	//	-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//	//	-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top Left 
//
//	//	-0.5f, 0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//	//	-0.5f, 0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//	//	-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//	//	-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top Left 
//
//	//	0.5f, 0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//	//	0.5f, 0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//	//	0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//	//	0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top Left 
//
//
//	//	0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//	//	0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//	//	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//	//	-0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top Left 
//
//
//	//	0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//	//	0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//	//	-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//	//	-0.5f, 0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
//
//
//	//};
//
//	//GLuint indices[] = {  // Note that we start from 0!
//	//	0, 1, 2, // First Triangle
//	//	0, 2, 3,// Second Triangle
//	//	4, 5, 6,
//	//	4, 6, 7,
//	//	7, 6, 2,
//	//	7, 2, 3,
//	//	4, 5, 1,
//	//	4, 1, 0,
//	//	4, 0, 3,
//	//	4, 3, 7,
//	//	5, 1, 2,
//	//	5, 2, 6
//	//};
//
//	GLfloat vertices[] = {
//		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,0.0f, 1.0f
//	};
//
//	GLuint VAO, VBO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
////	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
////	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	glBindVertexArray(0);
//
//	GLuint texture0, texture1;
//	//设置纹理1
//	glGenTextures(1, &texture0);
//	glBindTexture(GL_TEXTURE_2D, texture0);
//
//	//设置wrap和filter
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	unsigned char* imgWall = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgWall);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	SOIL_free_image_data(imgWall);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//
//	//设置纹理2
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	unsigned char* imgFace = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgFace);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	SOIL_free_image_data(imgFace);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	//设置变换
//	Shader ourShader("vShader.vs", "fShader.frag");
//
//	GLfloat parameter = 0;
//	glm::vec3 transform[] =
//	{
//		glm::vec3(0.0f, 0.0f, 0.0f),
//		glm::vec3(1.0f, 0.5f, -2.0f),
//		glm::vec3(-1.0f, 1.0f, -3.0f),
//		glm::vec3(2.0f, -0.3f, -0.5f),
//		glm::vec3(1.0f, -0.5f, -3.0f)
//	};
//	glm::mat4 matrix;
//	GLfloat ro1 = 0;
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		glEnable(GL_DEPTH_TEST);
//		glClearColor(0.0, 1.0, 1.0, 0.0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		ourShader.Use();
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture0);	//绑定纹理
//		GLuint tex0ID = glGetUniformLocation(ourShader.Program, "Texture0");
//		glUniform1i(tex0ID, 0);
//
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		GLuint tex1ID = glGetUniformLocation(ourShader.Program, "Texture1");
//		glUniform1i(tex1ID, 1);
//
//		GLuint mixID = glGetUniformLocation(ourShader.Program, "mixParameter");
//		glUniform1f(mixID, mixParameter);
//
//		if (parameter >= 360) parameter = 0;
//		else parameter += 0.1f;
//		glm::mat4 model, view, projection;
//
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
//		projection = glm::perspective(glm::radians(20.0f), 1.0f, 0.1f, 100.0f);
//
//		GLuint modelID, viewID, projectionID;
//		modelID = glGetUniformLocation(ourShader.Program, "model");
//		viewID = glGetUniformLocation(ourShader.Program, "view");
//		projectionID = glGetUniformLocation(ourShader.Program, "projection");
//
//		glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));
//
//		GLfloat ro = 0.0f;
//		ro1 += 0.1;
//		glBindVertexArray(VAO);
//
//		model = glm::translate(model, transform[0]);
//
//		if (ro1 < 360) {
//
//			ro1 += 0.1f;
//
//		}
//		else {
//			ro1 = 0.0f;
//		}
//		
//		model = glm::rotate(model, glm::radians(ro1), glm::vec3(1.0f, 0.5f, 0.0f));
//		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		
//
//		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
//		for (GLint i = 1; i < 5; i++)
//		{
//			ro += 20.0f * i;
//			model = glm::translate(model,transform[i]);
//			model = glm::rotate(model, glm::radians(ro), glm::vec3(0.5f, 1.0f, 0.5f));
//			glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		
//		
////		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
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
//	else if (key == GLFW_KEY_UP && action == GLFW_PRESS && mixParameter <= 1)
//	{
//		mixParameter += 0.1;
//	}
//	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && mixParameter >= 0)
//	{
//		mixParameter -= 0.1;
//	}
//}
//
