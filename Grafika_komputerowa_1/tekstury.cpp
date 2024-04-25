/*#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
using namespace std;
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void drawRectangle(GLfloat* vertices, GLuint* indices);
void drawTriangle(GLfloat* vertices, GLuint* indices);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);


const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"layout(location = 2) in vec2 textureCoord;\n"
"out vec3 vertexColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 1.0);\n"
"    vertexColor = color;\n"
"    TexCoord = textureCoord;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"in vec2 TexCoord;\n"
"out vec4 fragColor;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"uniform float mixFactor;\n"
"void main()\n"
"{\n"
"    fragColor = mix(texture(texture1, TexCoord), vec4(0.0, 0.0, 1.0, 1.0), mixFactor);\n"
"}\0";

float mixFactor = 0.0f;
GLuint VAO, VBO, EBO;
bool ifRectangle = false;
bool ifTriangle = false;
GLint uColorLocation;
GLuint shaderProgram;
GLuint texture1;
GLuint texture2;
GLfloat rectangleVertices[] = {
    // coordinates          // colors           // texture coords
    -0.8f,  0.8f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // triangle 1 vertex 1
    -0.8f, 0.2f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // triangle 1 vertex 2
     -0.2f, 0.2f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // triangle 1 vertex 3
     -0.2f,  0.8f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 1.0f  // triangle 2 vertex 1
};

GLuint rectangleIndices[] = {
    0, 1, 2,    // triangle 1
    0, 2, 3     // triangle 2
};
GLfloat triangleVertices[] = {
    // coordinates          // colors           // texture coords
    0.2f,  -0.2f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // triangle 1 vertex 1
    0.2f, -0.8f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // triangle 1 vertex 2
     0.8f, -0.8f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // triangle 1 vertex 3
};

GLuint triangleIndices[] = {
    0, 1, 2,    // triangle 1
};

void drawSquare()
{
    glUseProgram(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);
    GLint mix = glGetUniformLocation(shaderProgram, "mixFactor");
    glUniform1f(mix, mixFactor);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
void drawTriangle()
{
    glUseProgram(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(VAO);
    GLint mix = glGetUniformLocation(shaderProgram, "mixFactor");
    glUniform1f(mix, mixFactor);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}


void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_1)
        {
            ifRectangle = 1;
            ifTriangle = 0;
        }
        else if (key == GLFW_KEY_2)
        {
            ifTriangle = 1;
            ifRectangle = 0;
        }
        else if (key == GLFW_KEY_3)
        {
            ifTriangle = 1;
            ifRectangle = 1;
        }
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    mixFactor += 0.1f * yoffset;
    if (mixFactor < 0.0f) mixFactor = 0.0f;
    if (mixFactor > 1.0f) mixFactor = 1.0f;

    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "mixFactor"), mixFactor);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const unsigned int window_width = 1000;
    const unsigned int window_height = 800;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, error_message);
        std::cout << "Error (Vertex shader): " << error_message << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, error_message);
        std::cout << "Error (Fragment shader): " << error_message << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, error_message);
        std::cout << "Error (Shader program): " << error_message << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    uColorLocation = glGetUniformLocation(shaderProgram, "mixFactor");

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);


    GLubyte* data1 = stbi_load("image1.jpg", &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    GLubyte* data2 = stbi_load("image2.jpg", &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindVertexArray(VAO);
    GLint mix = glGetUniformLocation(shaderProgram, "mixFactor");
    glUniform1f(mix, mixFactor);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glViewport(0, 0, window_width, window_height);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (ifRectangle) {
            drawSquare();
        }
        if (ifTriangle) {
            drawTriangle();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}*/