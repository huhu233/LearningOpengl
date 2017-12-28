//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
//#include<iostream>
//#include"Shader.h"
//
//GLfloat degree = 0.0f;
//GLint bline = 1;
//GLfloat y = 1.0;
//
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	else if (key == GLFW_KEY_UP)
//	{
//		//degree += 20.0;
//		y += 0.1f;
//	}
//	else if (key == GLFW_KEY_DOWN)
//	{
//		//degree -= 20.0;
//		y -= 0.1f;
//	}
//	else if (key == GLFW_KEY_W)
//	{
//		bline = 1;
//	}
//	else if (key == GLFW_KEY_S)
//	{
//		bline = 0;
//	}
//}
//
//glm::vec3 lightSource;
//glm::vec3 viewSource(0.5f, -0.5f, 1.0f);
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow *window = glfwCreateWindow(800, 800, "Lignting", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window, key_callback);
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
//
//	GLfloat vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//
//	GLuint ObjVAO, LampVAO, ObjVBO, LampVBO;
//
//	glGenVertexArrays(1, &ObjVAO);
//	glGenVertexArrays(1, &LampVAO);
//	glGenBuffers(1, &ObjVBO);
//	glGenBuffers(1, &LampVBO);
//	
//	//set Object
//	glBindVertexArray(ObjVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, ObjVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(0));
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glBindVertexArray(0);	
//
//	//set Lamp
//	glBindVertexArray(LampVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, LampVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0));
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	Shader objShader("objVShader.vs", "objfragShader.frag");
//	Shader LampShader("shader/lightVShader.vs", "shader/lighterShader.frag");
//
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//
//	while (!glfwWindowShouldClose(window))
//	{	
//		glfwPollEvents();
//		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 objModel, lighterModel, view, projection;
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
//		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
//		//draw Object
//		objShader.Use();
//		GLuint objcolorID = glGetUniformLocation(objShader.Program, "objColor");
//		glUniform3f(objcolorID, 1.0f, 0.5f, 0.31f);
//		GLuint lightcolorID = glGetUniformLocation(objShader.Program, "lightColor");
//		glUniform3f(lightcolorID, 1.0f, 1.0f, 1.0f);
//
//		objModel = glm::translate(objModel, glm::vec3(0.0f, -0.5f, 0.0f));
//		objModel = glm::rotate(objModel, glm::radians(45.0f), glm::vec3(1.0f, 3.0f, 0.5f));
//		glUniformMatrix4fv(glGetUniformLocation(objShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(objModel));
//		glUniformMatrix4fv(glGetUniformLocation(objShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(glGetUniformLocation(objShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//		lightSource = glm::vec3(0.0f, y, 0.0f);
////		lightSource = glm::vec3(cos(glm::radians(degree)) * 0.5 , 0.5f, sin(glm::radians(degree)) * 2);
//		glUniform3f(glGetUniformLocation(objShader.Program, "lightSource"),lightSource.x, lightSource.y, lightSource.z);
////		glUniform3f(glGetUniformLocation(objShader.Program, "lightSource"), viewSource.x, viewSource.y, viewSource.z);
//		glUniform3f(glGetUniformLocation(objShader.Program, "viewSource"), viewSource.x, viewSource.y, viewSource.z);
//		glUniform1ui(glGetUniformLocation(objShader.Program, "bline"), bline);
//
//		glBindVertexArray(ObjVAO);	
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		
//		glBindVertexArray(0);
//
//		//draw Lamp
//		LampShader.Use();
//		lighterModel = glm::translate(lighterModel, lightSource);
//		lighterModel = glm::rotate(lighterModel, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		lighterModel = glm::scale(lighterModel, glm::vec3(0.2f));
//
//		glUniformMatrix4fv(glGetUniformLocation(LampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(lighterModel));
//		glUniformMatrix4fv(glGetUniformLocation(LampShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(glGetUniformLocation(LampShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		glBindVertexArray(LampVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//	
//	//freeBuffer
//	glDeleteBuffers(1, &ObjVBO);
//	glDeleteBuffers(1, &LampVBO);
//	glDeleteVertexArrays(1, &ObjVAO);
//	glDeleteVertexArrays(1, &LampVAO);
//	glfwTerminate();
//	return 0;
//}
//
//
