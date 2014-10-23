//
//  cube.h
//  metaheuristic
//
//  Created by ixi on 23/10/14.
//
//

#ifndef __metaheuristic__cube__
#define __metaheuristic__cube__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "model.h"

class Cube : public Model
{
public:
    /// Constructor.
    Cube(GLuint shader_program);
};

#endif /* defined(__metaheuristic__cube__) */
