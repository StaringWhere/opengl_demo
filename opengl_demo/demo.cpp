#pragma comment(linker,"/STACK:1024000000,1024000000") 

#include <glad/glad.h>//glad�ְ����Ż�����ָ�Ҫ�����а���OpenGL��ͷ�ļ�֮ǰ
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_s.h>
#include <math.h>
#include<windows.h>
#include<time.h>

#define SOLONG 30
#define AMOUNT 10000

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//char* readSource(const char* fileName);
int setField(Shader ourShader, unsigned int VAO, glm::vec4 field[][9]);
int move(glm::vec3* me, glm::vec4 fields[][9], unsigned int VAO, Shader ourShader, int count);
int genMe();

glm::vec4 fields[9][9];
glm::vec3** mes;

int main() {
	int success;
	char infoLog[512];

	//��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����

	//����4�������Ķ��ز������壬�ڴ�������֮ǰ
	glfwWindowHint(GLFW_SAMPLES, 4);

	//�������ں�������
	GLFWwindow* window = glfwCreateWindow(900, 900, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 900, 900);//������Ⱦ����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע��ص�����

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	////�������붥����ɫ��
	//char* vertexShaderSource = readSource("vertexShaderSource.txt");
	//unsigned int vertexShader;//����������ɫ������
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//�����ַ����������ַ�����NULL
	//glCompileShader(vertexShader);
	////�������Ƿ�ɹ�
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	////��������Ƭ����ɫ��
	//char* fragmentShaderSource = readSource("fragmentShaderSource.txt");
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	////�������Ƿ�ɹ�
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	////������ɫ���������
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	////���
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}

	//glDeleteShader(fragmentShader);
	//free(fragmentShaderSource);

	//�����µ�Ƭ����ɫ������
	//fragmentShaderSource = readSource("fragmentShaderSource2.txt");
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	////���
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << std::endl;
	//}
	//unsigned int shaderProgram2;
	//shaderProgram2 = glCreateProgram();
	//glAttachShader(shaderProgram2, vertexShader);
	//glAttachShader(shaderProgram2, fragmentShader);
	//glLinkProgram(shaderProgram2);
	////����
	//glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
	//	std::cout<< "ERROR::SHADER::PROGRAM2::LINK_FAILED\n" << infoLog << std::endl;
	//}

	////ɾ����ɫ������
	//glDeleteShader(vertexShader);
	//free(vertexShaderSource);


	//���û���ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float vertices[] = {
		-0.015f,0.015f,0.0f,
		0.015f,-0.015f,0.0f,
		0.00f,-0.015f,0.0f,
		0.015f,-0.015f,0.0f,
		0.015f,0.00f,0.0f,
		0.0f,0.0f,0.0f
	};
	float vertices2[] = {
		 0.0f, 0.0f, 0.0f,
		 0.0f,-0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f
	};
	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};
	//����VAO,VBO����
	unsigned int VAO[2],VBO[2];
	glGenVertexArrays(2, VAO);//��������������ͷָ��
	glGenBuffers(2, VBO);
	//��VAO[0]
	glBindVertexArray(VAO[0]);
	//�󶨡�д��VBO[0]
	glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//�������󶨡�д��EBO����VAO���ڼ䴴����EBO�ᱻ�Զ�д��VAO�����������ã���ζ��Ҫ�ڽ��VAO֮����EBO��
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//���ö�����������(��԰󶨵�VBO)��location��vec3���������ͣ�����׼������������ʼƫ����
	glEnableVertexAttribArray(0);//���ö�������ֵ������Ϊ���������λ��ֵ
	//���VBO,VAO,EBO����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//��VAO[1]
	glBindVertexArray(VAO[1]);
	//�󶨡�д��VBO[1]
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//���VBO,VAO����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//����ݡ��߿�
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(2);
	glPointSize(2);

	int count[AMOUNT] = {0};

	genMe();
	//Sleep(5000);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		//����
		processInput(window);

		//��Ⱦָ��
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		setField(ourShader, VAO[0], fields);
		for (int i = 0; i < AMOUNT; i++) {
			count[i] = move(mes[i], fields, VAO[0], ourShader, count[i]);
		}
		


		//��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);

		//Sleep(50);
	}

	glfwTerminate();
	return 0;
}

//�ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, height, height);
}

//��ⰴ������
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

////��Դ����
//char* readSource(const char* fileName) {
//	FILE* fp;
//	errno_t err = fopen_s(&fp, fileName, "rb");
//	if (err) {
//		std::cout << "can not open "<<fileName<<"\n" << std::endl;
//		return NULL;
//	}
//	fseek(fp, 0, SEEK_END);
//	int length = ftell(fp);
//	char* source = (char*)calloc((length + 1), sizeof(char));
//	if (source==NULL) {
//		std::cout << "ERROR::"<<fileName<<"::CALLOC_FAILED" << std::endl;
//		return NULL;
//	}
//	fseek(fp, 0, SEEK_SET);
//	char t;
//	for (int i = 0; i < length; i++) {
//		t = fgetc(fp);
//		source[i] = t;
//	}
//	return source;
//}

//�����������
int setField(Shader ourShader,unsigned int VAO,glm::vec4 field[][9]) {
	//�����������
	std::default_random_engine e;
	e.seed(18);
	std::uniform_real_distribution<float> u(-135.0f, 45.0f);

	//��ʼ������
	glm::mat4 trans = glm::mat4(1.0f);

	//��ɫ��
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

	glBindVertexArray(VAO);

	//�����ת����
	//trans = glm::rotate(trans, glm::radians(u(e)), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::translate(trans, glm::vec3(0.07f, 0.0f, 0.0f));
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//vec = trans * vec;
	//std::cout << vec.x<<" , "<< vec.y << " , " << vec.z << std::endl;


	int i, j;
	float t;
	glm::vec4 vec(1.0f, -1.0f, 0.0f, 1.0f);
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			//�任����
			trans = glm::translate(trans, glm::vec3(-0.68f + (j * 0.17f), -0.68f + (i * 0.17f), 0.0f));
			t = u(e);
			trans = glm::rotate(trans, glm::radians(t), glm::vec3(0.0, 0.0, 1.0));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			//��������
			trans = glm::mat4(1.0f);
			fields[i][j] = glm::rotate(trans, glm::radians(t), glm::vec3(0.0, 0.0, 1.0)) * vec;
			//��
			//glDrawArrays(GL_LINE_STRIP, 0, 5);
			//glDrawArrays(GL_POINTS, 1, 1);
			//�ָ�����
			trans = glm::mat4(1.0f);
		}
	}
	return 0;
}

int move(glm::vec3* me,glm::vec4 fields[][9],unsigned int VAO, Shader ourShader,int count) {
	glm::mat4 trans;
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glPointSize(1);
	glBindVertexArray(VAO);
	for (int i = 0; i < SOLONG; i++) {
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, *(me + i));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glDrawArrays(GL_POINTS, 5, 1);
	}
	glPointSize(2);

	float dist;
	glm::vec4 field;
	glm::vec4 next = { 0.0f,0.0f,0.0f,0.0f };
	float x, y;
	int flag = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			field = fields[i][j];
			x = -0.68 + 0.17*i;
			y = -0.68 + 0.17 * j;
			dist = (x - me->x) * (x - me->x) + (y - me->y) * (y - me->y);
			if (dist < 0.000001) {
				flag = 1;
				break;
			}
			next.x += field.x / dist/dist;
			next.y += field.y / dist/dist;
		}
		if (flag == 1){
			next.x += field.x;
			next.y += field.y;
			break;
		}
	}
	float mom = sqrt(next.x * next.x + next.y * next.y);
	next.x = next.x / mom * 0.001f;
	next.y = next.y / mom * 0.001f;
	//std::cout << next.x << " " << next.y << std::endl; 
	//std::cout << (me+count)->x << " " << (me + count)->y << std::endl;
	if (count == SOLONG-1) {
		(me + 0)->x = (me + count)->x + next.x;
		(me + 0)->y = (me + count)->y + next.y;
		count = 0;
	}
	else {
		(me + count + 1)->x = (me + count)->x + next.x;
		(me + count + 1)->y = (me + count)->y + next.y;
		count++;
	}
	return count;
}

int genMe() {
	mes = (glm::vec3 * *)calloc(AMOUNT, sizeof(glm::vec3*));
	for (int i = 0; i < AMOUNT; i++) {
		mes[i] = (glm::vec3*)calloc(SOLONG, sizeof(glm::vec3));
	}

	//�����������
	std::default_random_engine e;
	e.seed((unsigned)time(NULL));
	std::uniform_real_distribution<float> u(-1.0f, 1.0f);

	for (int i = 0; i < AMOUNT; i++) {
		mes[i][0].x = u(e);
		mes[i][0].y = u(e);
		mes[i][0].z = u(e);
		for (int j = 1; j < SOLONG; j++) {
			mes[i][j].x = mes[i][0].x;
			mes[i][j].y = mes[i][0].y;
			mes[i][j].z = mes[i][0].z;
		}
	}
	return 0;
}