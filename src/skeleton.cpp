#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 



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