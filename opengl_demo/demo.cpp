#include <glad/glad.h>//glad种包含优化过的指令，要在所有包含OpenGL的头文件之前
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
char* readSource(const char* fileName);

int main() {
	int success;
	char infoLog[512];

	//初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心

	//创建窗口和上下文
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 800, 600);//设置渲染区域
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数

	//创建编译顶点着色器
	char* vertexShaderSource = readSource("vertexShaderSource.txt");
	unsigned int vertexShader;//创建顶点着色器对象
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//对象，字符串数量，字符串，NULL
	glCompileShader(vertexShader);
	//检测编译是否成功
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//创建编译片段着色器
	char* fragmentShaderSource = readSource("fragmentShaderSource.txt");
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//检测编译是否成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//创建着色器程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//检测
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(fragmentShader);
	free(fragmentShaderSource);

	//创建新的片段着色器对象
	fragmentShaderSource = readSource("fragmentShaderSource2.txt");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//检测
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << std::endl;
	}
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader);
	glLinkProgram(shaderProgram2);
	//检验
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout<< "ERROR::SHADER::PROGRAM2::LINK_FAILED\n" << infoLog << std::endl;
	}

	//删除着色器对象
	glDeleteShader(vertexShader);
	free(vertexShaderSource);


	//设置绘制模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.7f, 0.5f, 0.0f,
		0.7f, 0.7f, 0.0f,
		0.5f, 0.7f, 0.0f,
		0.4f, 0.6f, 0.0f,
		0.5f, 0.5f, 0.5f
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


	//渲染循环
	while (!glfwWindowShouldClose(window)) {
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);//模式，起始索引，定点数量

		//检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

//回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//检测按键输入
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//读源代码
char* readSource(const char* fileName) {
	FILE* fp;
	errno_t err = fopen_s(&fp, fileName, "rb");
	if (err) {
		std::cout << "can not open "<<fileName<<"\n" << std::endl;
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	char* source = (char*)calloc((length + 1), sizeof(char));
	if (source==NULL) {
		std::cout << "ERROR::"<<fileName<<"::CALLOC_FAILED" << std::endl;
		return NULL;
	}
	fseek(fp, 0, SEEK_SET);
	char t;
	for (int i = 0; i < length; i++) {
		t = fgetc(fp);
		source[i] = t;
	}
	return source;
}