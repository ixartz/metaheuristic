//
//  window.cpp
//  metaheuristic
//
//  Created by ixi on 19/10/14.
//
//

#include "window.h"

void Window::window_resized(GLFWwindow* window, int width, int height)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}
