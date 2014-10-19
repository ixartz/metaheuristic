//
//  keyboard.cpp
//  metaheuristic
//
//  Created by ixi on 19/10/14.
//
//

#include "keyboard.h"

void Keyboard::key_callback(GLFWwindow* window,
                            int key,
                            int __attribute__((__unused__)) scancode,
                            int action,
                            int __attribute__((__unused__)) mods)
{
    if (action == GLFW_RELEASE || action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}