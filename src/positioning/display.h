//
//  display.h
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#ifndef __metaheuristic__display__
#define __metaheuristic__display__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../model/cube.h"
#include "../model/line.h"

class Display
{
public:
    /// Constructor
    Display(GLuint shader_program);

    /**
     * \brief Render the positioning of the electronic components.
     */
    void render(glm::mat4& mv);

private:
    GLuint shader_program_;

    Cube c_;
};

#endif /* defined(__metaheuristic__display__) */
