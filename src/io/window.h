//
//  window.h
//  metaheuristic
//
//  Created by ixi on 19/10/14.
//
//

#ifndef __metaheuristic__window__
#define __metaheuristic__window__

#include <GLFW/glfw3.h>

class Window
{
public:
    static void window_resized(GLFWwindow* window, int width, int height);
};

#endif /* defined(__metaheuristic__window__) */
