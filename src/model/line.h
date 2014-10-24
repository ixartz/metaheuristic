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
    Line(GLuint shader_program, std::vector<int>& loc);

    /**
     * \brief Render the model.
     */
    virtual void render(glm::mat4& mvp);

private:
    /**
     * \brief Create link between two nodes.
     */
    void create_link_(int src, int dst, std::vector<int>& loc);
};

#endif /* defined(__metaheuristic__line__) */
