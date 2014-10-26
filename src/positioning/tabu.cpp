//
//  tabu.cpp
//  metaheuristic
//
//  Created by ixi on 26/10/14.
//
//

#include "tabu.h"

Tabu::Tabu(Display& d)
    : eng_(time(NULL))
    , list_(5, std::make_pair(0, 0))
    , pos_(0)
    , d_(d)
{

}

void Tabu::search()
{
    std::vector<int>& loc = d_.get_loc();
    float min = std::numeric_limits<float>::max();
    int best1 = 0, best2 = 0, elt1, elt2;

    for (int i = 0; i < 100; ++i)
    {
        do
        {
            elt1 = uint_dist_(eng_) % loc.size();

            do
            {
                elt2 = uint_dist_(eng_) % loc.size();
            }
            while (elt1 == elt2);
        }
        while (std::find_if(list_.begin(), list_.end(),
                            [elt1, elt2] (std::pair<int, int>& p)
                            {
                                return (elt1 == p.first && elt2 == p.second) ||
                                        (elt2 == p.first && elt1 == p.second);
                            }) != list_.end());

        std::swap(loc[elt1], loc[elt2]);
        float cost = d_.compute_cost();

        if (min > cost)
        {
            min = cost;
            best1 = elt1;
            best2 = elt2;
        }

        // Reset the permutation
        std::swap(loc[elt1], loc[elt2]);
    }

    if (best1 != 0 || best2 != 0)
    {
        std::swap(loc[best1], loc[best2]);
        std::cout << min << std::endl;
        list_[pos_] = std::make_pair(best1, best2);
        next_pos_();
    }
}

void Tabu::next_pos_()
{
    ++pos_;

    if (pos_ == list_.size())
    {
        pos_ = 0;
    }
}