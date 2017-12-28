//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
//#include<iostream>
//#include<SOIL/SOIL.h>
//#include"Shader.h"
//using namespace std;
//
//GLfloat viewPos = -1;
//void key_callback(GLFWwindow *window, int key, int scancode, int action ,int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
//	{
//		if (viewPos < -1) viewPos++;
//	}
//	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
//	{
//		viewPos--;
//	}
//}
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
//	GLfloat cubeVertices[] = {
//		// Positions          // Texture Coords
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	GLfloat vertices[] =
//	{
//		3.0f, 3.0f, -0.5f, 1.0f, 1.0f,
//		3.0f, -3.0f, -0.5f, 1.0f, 0.0f,
//		-3.0f, -3.0f, -0.5f, 0.0f, 0.0f,
//		3.0f, 3.0f, -0.5f, 1.0f, 1.0f,
//		-3.0f, -3.0f, -0.5f, 0.0f, 0.0f,
//		-3.0f, 3.0f, -0.5f, 0.0f, 1.0f
//
//	};
//	GLuint VOA, BOA;
//	glGenVertexArrays(1, &VOA);
//	glGenBuffers(1, &BOA);
//
//	//开启顶点属性
//	glBindVertexArray(VOA);
//	glBindBuffer(GL_ARRAY_BUFFER, BOA);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(0));
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glBindVertexArray(1);
//
//	GLuint VOAFloor, BOAFloor;
//	glGenVertexArrays(1, &VOAFloor);
//	glGenBuffers(1, &BOAFloor);
//	glBindVertexArray(VOAFloor);
//	glBindBuffer(GL_ARRAY_BUFFER, BOAFloor);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(0));
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glBindVertexArray(0);
//
//	GLuint texture0;
//	glGenTextures(1, &texture0);
//	glBindTexture(GL_TEXTURE_2D, texture0);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	unsigned char*img = NULL;
//	img = SOIL_load_image("image/container.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
//	SOIL_free_image_data(img);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	Shader depthShader("shader/depthVShader.vs", "shader/depthFShader.frag");
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		glEnable(GL_DEPTH_TEST);
//		//render
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		
//		glm::mat4 model1, model2, view, projection;
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, viewPos));
//		projection = glm::perspective(glm::radians(45.0f),1.0f, 0.1f, 100.0f);
//		depthShader.Use();
//		//设置纹理
//		glActiveTexture(texture0);
//		glBindTexture(GL_TEXTURE_2D, texture0);
//		GLuint tex0ID = glGetUniformLocation(depthShader.Program, "texture0");
//		glUniform1i(tex0ID, 0);
//
//		GLuint viewID, modelID, projectionID;
//		viewID = glGetUniformLocation(depthShader.Program, "view");
//		modelID = glGetUniformLocation(depthShader.Program, "model");
//		projectionID = glGetUniformLocation(depthShader.Program, "projection");
//
//		glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));
//		glBindVertexArray(VOA);
//		model1 = glm::rotate(model1, glm::radians(-65.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//	//	model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model1));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
//		glBindVertexArray(0);
//
//		glBindVertexArray(VOAFloor);
//	//	model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, 0.0f));
//	//	model2 = glm::rotate(model2, glm::radians(-65.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//	//	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model1));
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		glBindVertexArray(0);
//
//		//reflesh buffer
//		glfwSwapBuffers(window);
//	}
//	
//	glDeleteBuffers(1, &BOA);
//	glDeleteVertexArrays(1, &VOA);
//	glDeleteBuffers(1, &BOAFloor);
//	glDeleteVertexArrays(1, &VOAFloor);
//	glfwTerminate();
//	return 0;
//
//}
//
//
