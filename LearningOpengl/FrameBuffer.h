#pragma once
#include<Eigen/Core>
#include<Eigen/Dense>
#include<GL/glew.h>
#include<vector>
#include<cstring>
#include<glm/glm.hpp>
#include "Triple.h"
class FrameBuffer {
public:
	FrameBuffer() :m_width(0), m_height(0) {}
	FrameBuffer(GLuint width, GLuint height)
	{
		m_width = width;
		m_height = height;
		m_buffer.resize(width * height * 3);
	}
	void resizeBuffer(int width, int height)
	{
		assert(width > 0 && height > 0);
		m_buffer.clear();
		m_buffer.resize(width * height * 3);
		m_width = width;
		m_height = height;
	}
	void init(/*glm::uvec3 bgColor*/ glm::vec3 bgColor)
	{
		memset(&m_buffer[0], 0, m_buffer.size());
		for (int i = 0; i < m_buffer.size(); i += 3)
		{
			m_buffer[i] = bgColor[0];
			m_buffer[i + 1] = bgColor[1];
			m_buffer[i + 2] = bgColor[2];
		}
	}
	GLuint getFrameBufferWidth() { return m_width; }
	GLuint getFrameBufferHeight() { return m_height; }

	void setPixel(GLuint x, GLuint y, glm::vec3 &color)
	{
		*(&m_buffer[0] + (y * m_width + x) * 3) = color.x;
		*(&m_buffer[0] + (y * m_width + x) * 3 + 1) = color.y;
		*(&m_buffer[0] + (y * m_width + x) * 3 + 2) = color.z;
		
	}


	Triple *getPixelAddress(GLuint x, GLuint y)
	{
		return (Triple*)(&m_buffer[0] + (y * m_width + x) * 3);
	}
	
private:
	GLuint m_width;
	GLuint m_height;
	//std::vector<GLubyte> m_buffer;
	std::vector<GLfloat> m_buffer;	//设定为浮点数在drawPixel时会出现异常，应该有精度上的问题
};