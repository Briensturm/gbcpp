#include <iostream>

#include <GLFW/glfw3.h>

int main()
{
    if(!glfwInit())
    {
        std::cout << "Error occured during glfw init." << std::endl;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
 
    glfwTerminate();

    exit(EXIT_SUCCESS);
}