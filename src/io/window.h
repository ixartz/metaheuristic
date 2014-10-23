//
//  window.h
//  metaheuristic
//
//  Created by ixi on 19/10/14.
//
//

#ifndef __metaheuristic__window__
#define __metaheuristic__window__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "../model/shader-loader.h"
#include "../model/cube.h"
#include "keyboard.h"
#include "Config.h"

class Window
{
public:
    /// Constructor.
    Window();
    /// Destructor.
    ~Window();

    /**
     * \brief Set window hints.
     */
    void create_hint();

    /**
     * \brief Create callback.
     */
    void create_callback();

    /**
     * \brief Print OpenGL version.
     */
    void print_version();

    /**
     * \brief Check glfw library.
     */
    void check_glfw();

    /**
     * \brief Check glew library.
     */
    void check_glew();

    /**
     * \brief Execute the display.
     */
    void execute();

    /**
     * \brief Called when the window is resized.
     */
    static void window_resized(GLFWwindow* window, int width, int height);

private:
    GLFWwindow* window_;
    GLuint shader_program_;
};

#endif /* defined(__metaheuristic__window__) */
