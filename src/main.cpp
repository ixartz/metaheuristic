#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "io/window.h"
#include "io/keyboard.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(640, 320, "Metaheuristic", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to open a window!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, Keyboard::key_callback);
    glfwSetWindowSizeCallback(window, Window::window_resized);
    glOrtho(0, 640, 320, 0, 0, 1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
