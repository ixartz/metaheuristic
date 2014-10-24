//
//  model.h
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#ifndef __metaheuristic__model__
#define __metaheuristic__model__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../model/shader-loader.h"

class Model
{
public:
    /// Constructor.
    Model(GLuint shader_program);

    /**
     * \brief Render the model.
     */
    virtual void render(glm::mat4& mvp);

protected:
    /**
     * \brief Initialize elements for the shader.
     */
    void init_();

protected:
    GLuint shader_program_;

    GLuint vao_;
    GLuint vbo_;
    GLuint eab_;

    GLint mvp_uniform_;

    std::vector<GLfloat> vertice_pos_;
    std::vector<GLfloat> color_;
    std::vector<GLfloat> normal_;
    std::vector<GLuint> indice_;
};

#endif /* defined(__metaheuristic__model__) */
