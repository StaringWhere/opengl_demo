#include <glad/glad.h>//glad�ְ����Ż�����ָ�Ҫ�����а���OpenGL��ͷ�ļ�֮ǰ
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
char* readSource(const char* fileName);

int main() {
	int success;
	char infoLog[512];

	//��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����

	//�������ں�������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 800, 600);//������Ⱦ����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע��ص�����

	//�������붥����ɫ��
	char* vertexShaderSource = readSource("vertexShaderSource.txt");
	unsigned int vertexShader;//����������ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//�����ַ����������ַ�����NULL
	glCompileShader(vertexShader);
	//�������Ƿ�ɹ�
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//��������Ƭ����ɫ��
	char* fragmentShaderSource = readSource("fragmentShaderSource.txt");
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//�������Ƿ�ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//������ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//���
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(fragmentShader);
	free(fragmentShaderSource);

	//�����µ�Ƭ����ɫ������
	fragmentShaderSource = readSource("fragmentShaderSource2.txt");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//���
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
	//����
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout<< "ERROR::SHADER::PROGRAM2::LINK_FAILED\n" << infoLog << std::endl;
	}

	//ɾ����ɫ������
	glDeleteShader(vertexShader);
	free(vertexShaderSource);


	//���û���ģʽ
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


	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		//����
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);//ģʽ����ʼ��������������

		//��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

//�ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//��ⰴ������
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//��Դ����
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