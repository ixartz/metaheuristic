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

class Display;

class Line : public Model
{
public:
    /// Constructor.
    Line(GLuint shader_program, Display* d);

    /**
     * \brief Render the model.
     */
    virtual void render(glm::mat4& mvp);

private:
    /**
     * \brief Create link between two nodes.
     */
    void create_link_(int src, int dst, Display* d);
};

#endif /* defined(__metaheuristic__line__) */
