//#include<gl/glew.h>
//#include<GLFW/glfw3.h>
//#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
//#include<iostream>
//#include<vector>
//#include"Shader.h"
//using namespace std;
//
//
//GLdouble x = 0, y = 0;
//GLdouble xOff = 0, yOff = 0;
//GLuint VAO, BAO;
//vector<glm::vec3> tmp;
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
//void mouse_callback(GLFWwindow *window, int button, int action, int mode)
//{
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//	{
//		GLdouble x, y;
//		glm::vec3 v;
//		glfwGetCursorPos(window, &x, &y);
//		v.x = x;
//		v.y = y;
//		v.z = 0.0;
//		v = glm::normalize(v);
//		tmp.push_back(v);
//		glBindVertexArray(VAO);
//		glBindBuffer(GL_ARRAY_BUFFER, BAO);
//		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLdouble) * tmp.size(), &tmp[0], GL_STATIC_DRAW);
//		glBindVertexArray(0);
//		cout << tmp.size() << endl;
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
//	glfwSetMouseButtonCallback(window, mouse_callback);
//
//
//	Vertex v;
//	v.xpos = 0.0;
//	v.ypos = 0.0;
//	v.zpos = 0.0;
//	tmp.push_back(v);
//	//v.xpos = -0.5;
//	//v.ypos = 0.0;
//	//v.zpos = 0.0;	
//	//tmp.push_back(v);
//	//v.xpos = 0.0;
//	//v.ypos = 0.5;
//	//v.zpos = 0.0;
//	//tmp.push_back(v);
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &BAO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, BAO);
//	glBufferData(GL_ARRAY_BUFFER, tmp.size() * sizeof(Vertex), &tmp[0], GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_DOUBLE, sizeof(Vertex), (void*)(0));
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//	Shader skeShader("shader/vSkeleton.vs", "shader/fSkeleton.frag");
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		skeShader.Use();
//		/*glDrawArrays(GL_POINTS, 0, tmp.size());*/
//	//	glColor3f(1.0f, 0.0f, 0.0f);
//	/*	glBegin(GL_LINES);
//		glVertex2d(20.0f, 30.0f);
//		glVertex2d(100.0f, 200.0f);
//		glEnd();*/
//		glBindVertexArray(VAO);
//
//		glDrawArrays(GL_LINE_STRIP, 0, tmp.size());
//
//		glBindVertexArray(0);
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &BAO);
//	glfwTerminate();
//	
//	return 0;
//}