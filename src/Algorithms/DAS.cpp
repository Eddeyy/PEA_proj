//
// Created by thero on 19.01.2023.
//
#include <DAS.h>

void DAS::update(floatMatrix &tau, intMatrix& paths, const intMatrix& adj_mat)
{
    float update_value = 10.f;

    for(auto & path : paths)
    {
        int from = path[path.size()-2];
        int to = path[path.size()-1];

        tau[from][to] += update_value;
        tau[to][from] += update_value;
    }

}