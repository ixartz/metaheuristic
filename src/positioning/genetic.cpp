//
//  genetic.cpp
//  metaheuristic
//
//  Created by ixi on 26/10/14.
//
//

#include "genetic.h"

Genetic::Genetic(std::vector<int>& loc)
    : eng_(time(NULL))
    , pop_(100, loc)
{

}

void Genetic::mutate()
{
    for (unsigned i = 0; i < pop_.size(); ++i)
    {
        int elt1 = uint_dist_(eng_) % pop_[i].size();
        int elt2;

        do
        {
            elt2 = uint_dist_(eng_) % pop_[i].size();
        }
        while (elt1 == elt2);

        std::swap(pop_[i][elt1], pop_[i][elt2]);
    }
}

std::vector<int> Genetic::cross_over(int l, int r)
{
    std::vector<int> res;

    for (unsigned i = 0; i < pop_[l].size(); ++i)
    {
        if (uint_dist_(eng_) % 2)
            res.push_back(pop_[l][i]);
        else
            res.push_back(pop_[r][i]);
    }

    return res;
}

std::vector<int>& Genetic::get_best()
{
    return pop_[0];
}