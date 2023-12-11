#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std; 

const int steps = 50;
const float stepAngle = 3.1415926f * 2.f / steps;


int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    window = glfwCreateWindow(700,600, "Hello World", 0, 0);
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

    float xPos = 0; float yPos = 0; float radius = 1.0f;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
     
        glClearColor(1,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);

        float xCenter = 0.0f;
        float yCenter = 0.0f;
        float radius = 1.f;
        
        float rx = xCenter;
        float ry = yCenter-radius;
        
        for (int i=0;i<=steps;i++) {
            float angle = stepAngle*i;
            float newRx = radius*sinf(angle);
            float newRy = -radius*cosf(angle);
            glBegin(GL_TRIANGLES);
            glColor3f(0.f,0.75f,0.f);
            glVertex3f(0.f,0.f,0.f);
            glVertex3f(rx,ry,0.f);
            glVertex3f(newRx,newRy,0.f);
            glEnd();
            rx = newRx;
            ry = newRy;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
   
}