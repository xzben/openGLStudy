#include "test/RectItem.h"
#include <glad/glad.h>

RectItem::RectItem() 
	:m_va(0)
{
	float vertices[] = {
		//--- pos -------     ----- color ----   --- texture --
		  0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 右上角
		  0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,  1.0f, 0.0f,// 右下角
		  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,// 左下角
		  -0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f// 左上角
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	glGenVertexArrays(1, &this->m_va);
	glBindVertexArray(this->m_va);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//GL_STATIC_DRAW 代表绘制的数据不会或基本不会变
	//GL_DYNAMIC_DRAW：数据会被改变很多。
	//GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void RectItem::render()
{
	glBindVertexArray(this->m_va);
	//可以配置绘制多边形的方式，  GL_LINE 绘线 GL_FILL 填充 
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}