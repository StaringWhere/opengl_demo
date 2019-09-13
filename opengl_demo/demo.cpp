#pragma comment(linker,"/STACK:1024000000,1024000000") 

#include <glad/glad.h>//glad种包含优化过的指令，要在所有包含OpenGL的头文件之前
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

	//初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心

	//创建4个样本的多重采样缓冲，在创建窗口之前
	glfwWindowHint(GLFW_SAMPLES, 4);

	//创建窗口和上下文
	GLFWwindow* window = glfwCreateWindow(900, 900, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 900, 900);//设置渲染区域
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	////创建编译顶点着色器
	//char* vertexShaderSource = readSource("vertexShaderSource.txt");
	//unsigned int vertexShader;//创建顶点着色器对象
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//对象，字符串数量，字符串，NULL
	//glCompileShader(vertexShader);
	////检测编译是否成功
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	////创建编译片段着色器
	//char* fragmentShaderSource = readSource("fragmentShaderSource.txt");
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	////检测编译是否成功
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	////创建着色器程序对象
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	////检测
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}

	//glDeleteShader(fragmentShader);
	//free(fragmentShaderSource);

	//创建新的片段着色器对象
	//fragmentShaderSource = readSource("fragmentShaderSource2.txt");
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	////检测
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
	////检验
	//glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
	//	std::cout<< "ERROR::SHADER::PROGRAM2::LINK_FAILED\n" << infoLog << std::endl;
	//}

	////删除着色器对象
	//glDeleteShader(vertexShader);
	//free(vertexShaderSource);


	//设置绘制模式
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
	//创建VAO,VBO对象
	unsigned int VAO[2],VBO[2];
	glGenVertexArrays(2, VAO);//生成数量，数组头指针
	glGenBuffers(2, VBO);
	//绑定VAO[0]
	glBindVertexArray(VAO[0]);
	//绑定、写入VBO[0]
	glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//创建、绑定、写入EBO对象，VAO绑定期间创建的EBO会被自动写入VAO（包括解绑调用，意味着要在解绑VAO之后解绑EBO）
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//创建顶点指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//设置顶点属性配置(针对绑定的VBO)，location，vec3，数据类型，不标准化，步长，起始偏移量
	glEnableVertexAttribArray(0);//启用顶点属性值，参数为顶点的属性位置值
	//解绑VBO,VAO,EBO对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//绑定VAO[1]
	glBindVertexArray(VAO[1]);
	//绑定、写入VBO[1]
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//创建顶点指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//解绑VBO,VAO对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//抗锯齿、线宽
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(2);
	glPointSize(2);

	int count[AMOUNT] = {0};

	genMe();
	//Sleep(5000);

	//渲染循环
	while (!glfwWindowShouldClose(window)) {
		//输入
		processInput(window);

		//渲染指令
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		setField(ourShader, VAO[0], fields);
		for (int i = 0; i < AMOUNT; i++) {
			count[i] = move(mes[i], fields, VAO[0], ourShader, count[i]);
		}
		


		//检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);

		//Sleep(50);
	}

	glfwTerminate();
	return 0;
}

//回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, height, height);
}

//检测按键输入
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

////读源代码
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

//随机场正方形
int setField(Shader ourShader,unsigned int VAO,glm::vec4 field[][9]) {
	//创建随机对象
	std::default_random_engine e;
	e.seed(18);
	std::uniform_real_distribution<float> u(-135.0f, 45.0f);

	//初始化矩阵
	glm::mat4 trans = glm::mat4(1.0f);

	//着色器
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

	glBindVertexArray(VAO);

	//随机旋转矩阵
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
			//变换矩阵
			trans = glm::translate(trans, glm::vec3(-0.68f + (j * 0.17f), -0.68f + (i * 0.17f), 0.0f));
			t = u(e);
			trans = glm::rotate(trans, glm::radians(t), glm::vec3(0.0, 0.0, 1.0));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			//储存向量
			trans = glm::mat4(1.0f);
			fields[i][j] = glm::rotate(trans, glm::radians(t), glm::vec3(0.0, 0.0, 1.0)) * vec;
			//画
			//glDrawArrays(GL_LINE_STRIP, 0, 5);
			//glDrawArrays(GL_POINTS, 1, 1);
			//恢复矩阵
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

	//创建随机对象
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