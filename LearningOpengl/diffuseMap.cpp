//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
//#include<iostream>
//#include<SOIL/SOIL.h>
//#include"Shader.h"
//
//GLfloat degree = 0.0f;
//
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	else if (key == GLFW_KEY_UP && degree < 340.0)
//	{
//		degree += 10.0;
//	}
//	else if (key == GLFW_KEY_DOWN && degree > 20.0)
//	{
//		degree -= 10.0;
//	}
//}
//
//glm::vec3 lightSource;
//glm::vec3 viewSource(0.5f, -0.5f, 1.0f);
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
//		// Positions           // Normals           // Texture Coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//	};
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
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(0));
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindVertexArray(0);
//
//	//set Lamp
//	glBindVertexArray(LampVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, LampVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//// set texture0;
//	GLuint texture0;
//	glGenTextures(1, &texture0);
//	glBindTexture(GL_TEXTURE_2D, texture0);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	unsigned char* img;
//	img = SOIL_load_image("image/container.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
//	SOIL_free_image_data(img);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	Shader objShader("shader/vShader.vs", "shader/fShader.frag");
//	Shader LampShader("shader/lightVShader.vs", "shader/lighterShader.frag");
//
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
//			//set texture0
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture0);
//		GLuint tex0ID = glGetUniformLocation(objShader.Program, "material.diffuse");
//		glUniform1i(tex0ID, 0);
//		glUniform3f((glGetUniformLocation(objShader.Program, "material.specular")), 0.5f, 0.5f, 0.5f);
//		glUniform1f(glGetUniformLocation(objShader.Program, "material.shininess"), 32.0f);
//			//set light
//		glUniform3f(glGetUniformLocation(objShader.Program, "light.ambient"), 0.2f, 0.2f, 0.2f);
//		glUniform3f(glGetUniformLocation(objShader.Program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
//		glUniform3f(glGetUniformLocation(objShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
//		glUniform3f(glGetUniformLocation(objShader.Program, "light.position"), lightSource.x, lightSource.y, lightSource.z);
//
//		objModel = glm::translate(objModel, glm::vec3(0.0f, -0.5f, 0.0f));
//		objModel = glm::rotate(objModel, glm::radians(-45.0f), glm::vec3(1.0f, 1.3f, -0.5f));
//		glUniformMatrix4fv(glGetUniformLocation(objShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(objModel));
//		glUniformMatrix4fv(glGetUniformLocation(objShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(glGetUniformLocation(objShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//		lightSource = glm::vec3(cos(glm::radians(degree)) * 2, 1.2f, sin(glm::radians(degree)) * 2);
//		glUniform3f(glGetUniformLocation(objShader.Program, "lightSource"), lightSource.x, lightSource.y, lightSource.z);
//		glUniform3f(glGetUniformLocation(objShader.Program, "viewSource"), viewSource.x, viewSource.y, viewSource.z);
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
