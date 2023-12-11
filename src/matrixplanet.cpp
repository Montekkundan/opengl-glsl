#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std; 

const int steps = 100;
void drawCircle(float red, float green, float blue){
    float radius = 1.;
    const float angle = 2.0f * 3.1416f / steps;
    float oldX = 0; float oldY = 0;
    for (int i = 0; i <= steps; i++) {
        float newX = radius * sin(i * angle);
        float newY = radius * cos(i * angle);
        glColor3f(red, green, blue);
        glBegin(GL_TRIANGLES);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(oldX, oldY, 0.f);
        glVertex3f(newX, newY, 0.f);
        glEnd();

        oldX = newX;
        oldY = newY;
    }
}

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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(0.1, 0.1, 1);
    float angle = 0;
    float angleMoon = 0;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        angle += 1;
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        // sun
        drawCircle(0, 1, 0);
        {
            // earth
            glPushMatrix();
            glRotatef(angle, 0, 0, 1);
            glTranslatef(0,5,0);
            glScalef(0.5, 0.5, 1);
            drawCircle(0, 0.3, 1);
            {
                // moon
                glPushMatrix();
                glRotatef(angleMoon, 0, 0, 1);
                glTranslatef(0, 2, 0);
                glScalef(0.3, 0.3, 1);
                drawCircle(0.5, 0.5, 0.5);
                glPopMatrix();
                angleMoon += 5;
            
            }
            glPopMatrix();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
   
}