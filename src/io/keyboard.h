//
//  keyboard.h
//  metaheuristic
//
//  Created by ixi on 19/10/14.
//
//

#ifndef __metaheuristic__keyboard__
#define __metaheuristic__keyboard__

#include <GLFW/glfw3.h>

class Keyboard
{
public:
    /**
     * \brief Called when a key is pressed, repeated or released.
     */
    static void key_callback(GLFWwindow* window,
                             int key,
                             int scancode,
                             int action,
                             int mods);
};

#endif /* defined(__metaheuristic__keyboard__) */
