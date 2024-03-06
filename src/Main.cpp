#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <crtdbg.h>


#define _CRTDBG_MAP_ALLOC

static const int W_HEIGHT = 800;
static const int W_WIDTH = 600;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLuint createAndCompileShaderFromSourceCode(GLenum type, const char* sourceCode) {
    // Create shader object referenced by ID
    GLuint shader;
    shader = glCreateShader(type);

    // Assign shader source code to the shader object and compile shader
    glShaderSource(shader, 1, &sourceCode, nullptr);
    glCompileShader(shader);
    return shader;
}

void printShaderCompileStatus(GLuint shader) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void printShaderProgramLinkStatus(GLuint shaderProgram) {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(W_HEIGHT, W_WIDTH, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // I need one buffer ID (VBO stands for Vertex Buffer Object)
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // Bind our new VBO to Array Buffer type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy vertices to our created buffer. GL_STATIC_DRAW: the data is set only once and used many times.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    GLuint vertexShader = createAndCompileShaderFromSourceCode(GL_VERTEX_SHADER, vertexShaderSource);
    // Check compilation status
    printShaderCompileStatus(vertexShader);

    GLuint fragmentShader = createAndCompileShaderFromSourceCode(GL_FRAGMENT_SHADER, fragmentShaderSource);
    printShaderCompileStatus(fragmentShader);

    // Create shader program object
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    printShaderProgramLinkStatus(shaderProgram);

    glUseProgram(shaderProgram);

    // After linking shaders into the shader program; we no longer need them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Linking vertex attribute
    // How OpenGL should interpret the vertex data
    // Vertex: 32 bit (4 byte) floating point
    // First param: layout (location = 0) sets the location of the vertex attribute to 0 so we pass 0
    // Second param: size of the vertex attribute (vec3)
    // Third param: type of the data
    // Fourth param: if we want the data to be normalized 
    // Fifth param: stride
    // Six param: offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the vertex attribute
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return 0;
}
