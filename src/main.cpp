#include <GL/glew.h>
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

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

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

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    std::cout << "OpenGL - " << major << "."
              << minor << "." << rev << std::endl;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

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
