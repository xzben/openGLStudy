#include "test/RectItem.h"
#include <glad/glad.h>

RectItem::RectItem() 
	:m_va(0)
{
	float vertices[] = {
		//--- pos -------     ----- color ----   --- texture --
		  0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // ���Ͻ�
		  0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,  1.0f, 0.0f,// ���½�
		  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,// ���½�
		  -0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f// ���Ͻ�
	};

	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	glGenVertexArrays(1, &this->m_va);
	glBindVertexArray(this->m_va);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//GL_STATIC_DRAW ������Ƶ����ݲ������������
	//GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	//GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
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
	//�������û��ƶ���εķ�ʽ��  GL_LINE ���� GL_FILL ��� 
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}