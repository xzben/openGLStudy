#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "image/Image.h"
#include "test/RectItem.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void doDraw() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Shader shader("texture_shader.vs", "texture_shader.fs");
	Image image1("wall.jpg");
	Image image2("awesomeface.png");

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

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	image1.render();
	glActiveTexture(GL_TEXTURE1);
	image2.render();

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	glBindVertexArray(VAO);
	//�������û��ƶ���εķ�ʽ��  GL_LINE ���� GL_FILL ��� 
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

int main() 
{
	//��ʼ�� glfw
	glfwInit();
	
	//ָ��opengl �汾 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//ָ��ʹ��core �ں�ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	//Mac OS X ϵͳ��Ҫ����ע�ͣ�������ǰ����
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//ָ�����ڴ�С
	glViewport(0, 0, 800, 600);
	//���ô��ڴ�С�仯�ص�����Ҫ���ô��ڴ�С��
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	RectItem item;
	Shader shader("texture_shader.vs", "texture_shader.fs");
	Image image1("wall.jpg");
	Image image2("awesomeface.png");

	while (!glfwWindowShouldClose(window))
	{
		//�����������
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		image1.render();
		glActiveTexture(GL_TEXTURE1);
		image2.render();

		shader.use();
		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);
		item.render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

