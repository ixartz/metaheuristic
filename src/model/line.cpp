//
//  line.cpp
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#include "../positioning/display.h"
#include "line.h"

Line::Line(GLuint shader_program, Display* d)
    : Model(shader_program)
{
    for (unsigned i = 0; i < d->get_loc().size(); ++i)
    {
        if (i % 5 < 4)
        {
            create_link_(i, i + 1, d);
        }

        if (i / 5 < 4)
        {
            create_link_(i, i + 5, d);
        }
    }

    float ambient_light[4] = { 1.0, 1.0, 1.0, 1.0 };
    init_(ambient_light);
}

void Line::render(glm::mat4& mvp)
{
    Model::render(mvp);
    glDrawArrays(GL_LINES, 0, vertice_pos_.size());
}

void Line::create_link_(int src, int dst, Display* d)
{
    vertice_pos_.push_back(d->compute_x(src));
    vertice_pos_.push_back(d->compute_y(src));
    vertice_pos_.push_back(0.0f);

    vertice_pos_.push_back(d->compute_x(dst));
    vertice_pos_.push_back(d->compute_y(dst));
    vertice_pos_.push_back(0.0f);

    color_.push_back(1.0);
    color_.push_back(0.0);
    color_.push_back(0.0);

    color_.push_back(1.0);
    color_.push_back(0.0);
    color_.push_back(0.0);

    normal_.push_back(0.0f);
    normal_.push_back(0.0f);
    normal_.push_back(0.0f);
    normal_.push_back(0.0f);
    normal_.push_back(0.0f);
    normal_.push_back(0.0f);
}
