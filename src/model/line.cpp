//
//  line.cpp
//  metaheuristic
//
//  Created by ixi on 24/10/14.
//
//

#include "line.h"

Line::Line(GLuint shader_program, std::vector<int>& loc)
    : Model(shader_program)
{
    for (unsigned i = 0; i < loc.size(); ++i)
    {
        if (i % 5 < 4)
        {
            create_link_(i, i + 1, loc);
        }

        if (i / 5 < 4)
        {
            create_link_(i, i + 5, loc);
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

void Line::create_link_(int src, int dst, std::vector<int>& loc)
{
    vertice_pos_.push_back(loc[src] / 5 * -4.5f + 9.0f);
    vertice_pos_.push_back(loc[src] % 5 * -4.5f + 9.0f);
    vertice_pos_.push_back(0.0f);

    vertice_pos_.push_back(loc[dst] / 5 * -4.5f + 9.0f);
    vertice_pos_.push_back(loc[dst] % 5 * -4.5f + 9.0f);
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
