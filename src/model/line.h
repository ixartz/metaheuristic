//
//  line.h
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#ifndef __metaheuristic__line__
#define __metaheuristic__line__

#include "model.h"

class Line : public Model
{
public:
    /// Constructor.
    Line(GLuint shader_program);
    /// Destructor.
    virtual ~Line();

    /**
     * \brief Render the model.
     */
    virtual void render(glm::mat4& mvp);
};

#endif /* defined(__metaheuristic__line__) */
