#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 


// vertex shader source

const GLchar* vertex120 = R"END(
#version 120
attribute vec3 position;
attribute vec3 color;
varying vec3 outColor;
uniform float time;
uniform mat4 matrix;
void main()
{
    float theta = time;
    
    float co = cos(theta);
    float si = sin(theta);

    mat4 rotationY = mat4(co, 0, si, 0,
                          0, 1, 0, 0,
                         -si, 0, co, 0,
                         0, 0, 0, 1);

    mat4 rotationX = mat4(1, 0, 0, 0,
                          0, co, -si, 0,
                          0, si, co, 0,
                          0, 0, 0, 1);

    mat4 rotationZ = mat4(co, -si, 0, 0,
                      si, co, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);

    outColor = color;
    gl_Position = matrix * rotationX * rotationZ * vec4(position,1.f);
}
)END";

// fragment shader source

const GLchar* raster120 = R"END(
#version 120
varying vec3 outColor;
uniform float time;
void main()
{
    gl_FragColor = vec4(outColor,1);
}
)END";


int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    window = glfwCreateWindow(800, 800, "Hello World", 0, 0);
    if (!window)
    {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    std::cout << "Init :: checking OpenGL version:\n";
    const unsigned char * msg;
    msg = glGetString(GL_VERSION);
    std::cout << msg << "\n Shader language version: \n";
    msg = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << msg << "\n";
    
    const char* source;
    GLint compilationStatus;
    
    // ------------- VERTEX SHADER
    
    source = vertex120;
    
    GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVertex,1,&source,0);
    glCompileShader(shaderVertex);
    
    glGetShaderiv(shaderVertex, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderVertex, sizeof(messages), 0, &messages[0]); std::cout << messages;
        exit(1);
    }
    
    // ---------- FRAGMENT SHADER
    
    source = raster120;
    
    GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragment,1,&source,0);
    glCompileShader(shaderFragment);
    
    glGetShaderiv(shaderFragment, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderFragment, sizeof(messages), 0, &messages[0]); std::cout << messages;
        exit(1);
    }
    
    // ------------- SHADER PROGRAM
    
    GLint linkStatus;
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,shaderVertex);
    glAttachShader(shaderProgram,shaderFragment);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&linkStatus);
    if (linkStatus == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(shaderProgram,sizeof(messages),0,&messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    glUseProgram(shaderProgram);
    
    // ---------------- VBOs
    
    
    GLfloat vertices[] = {
    // Front face
    -1.0f, -1.0f,  1.0f, // Vertex 1
     1.0f, -1.0f,  1.0f, // Vertex 2
     1.0f,  1.0f,  1.0f, // Vertex 3
    -1.0f,  1.0f,  1.0f, // Vertex 4
    // Right face
     1.0f, -1.0f,  1.0f, // Vertex 5
     1.0f, -1.0f, -1.0f, // Vertex 6
     1.0f,  1.0f, -1.0f, // Vertex 7
     1.0f,  1.0f,  1.0f, // Vertex 8
    // Back face
     1.0f, -1.0f, -1.0f, // Vertex 9
    -1.0f, -1.0f, -1.0f, // Vertex 10
    -1.0f,  1.0f, -1.0f, // Vertex 11
     1.0f,  1.0f, -1.0f, // Vertex 12
    // Left face
    -1.0f, -1.0f, -1.0f, // Vertex 13
    -1.0f, -1.0f,  1.0f, // Vertex 14
    -1.0f,  1.0f,  1.0f, // Vertex 15
    -1.0f,  1.0f, -1.0f, // Vertex 16
    // Top face
    -1.0f,  1.0f,  1.0f, // Vertex 17
     1.0f,  1.0f,  1.0f, // Vertex 18
     1.0f,  1.0f, -1.0f, // Vertex 19
    -1.0f,  1.0f, -1.0f, // Vertex 20
    // Bottom face
    -1.0f, -1.0f, -1.0f, // Vertex 21
     1.0f, -1.0f, -1.0f, // Vertex 22
     1.0f, -1.0f,  1.0f, // Vertex 23
    -1.0f, -1.0f,  1.0f  // Vertex 24
};

GLfloat colors[] = {
    // Front face (Red)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    // Right face (Green)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    // Back face (Blue)
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    // Left face (Cyan)
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    // Top face (Magenta)
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    // Bottom face (Yellow)
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

GLubyte indices[] = {
    // Front face
    0,  1,  2,  2,  3,  0,
    // Right face
    4,  5,  6,  6,  7,  4,
    // Back face
    8,  9, 10, 10, 11,  8,
    // Left face
    12, 13, 14, 14, 15, 12,
    // Top face
    16, 17, 18, 18, 19, 16,
    // Bottom face
    20, 21, 22, 22, 23, 20
};
    
    GLuint verticesBuf;
    glGenBuffers(1, &verticesBuf);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint colorsBuf;
    glGenBuffers(1, &colorsBuf);
    glBindBuffer(GL_ARRAY_BUFFER, colorsBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint indicesBuf;
    glGenBuffers(1, &indicesBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // ----------------- attributes
    
    GLuint attribPosition;
    attribPosition = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(attribPosition);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuf);
    glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint attribColor;
    attribColor = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(attribColor);
    glBindBuffer(GL_ARRAY_BUFFER, colorsBuf);
    glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLfloat matrix[] = {
        0.5, 0, 0, 0,
        0, 0.5, 0, 0,
        0, 0, 0.5, 0,
        0, 0, 0, 1
    };
    
    GLuint attribMatrix;
    attribMatrix = glGetUniformLocation(shaderProgram, "matrix");
    glUniformMatrix4fv(attribMatrix, 1, GL_FALSE, matrix);
    
    GLuint uniformTime;
    uniformTime = glGetUniformLocation(shaderProgram, "time");
    
    

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffer as well
        
        float time = glfwGetTime();
        glUniform1f(uniformTime, time);
        
    
        
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
   
}