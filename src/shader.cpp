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

    outColor = color;
    gl_Position = matrix * rotationY * rotationX * vec4(position,1.f);
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

    window = glfwCreateWindow(640, 480, "Hello World", 0, 0);
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


    // render loop
    while (!glfwWindowShouldClose(window))
    {
     
        glClearColor(1.0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
   
}