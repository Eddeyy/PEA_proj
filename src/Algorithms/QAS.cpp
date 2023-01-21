//
// Created by thero on 20.01.2023.
//

#include <QAS.h>

void QAS::update(floatMatrix &tau, intMatrix &paths, const intMatrix& adj_mat)
{
    float update_value = 100;

    for(auto & path : paths)
    {
        int from = path[path.size()-2];
        int to = path[path.size()-1];

        double cost = (adj_mat[from][to] == 0)? 0.1 : adj_mat[from][to];

        tau[from][to] += update_value/(float)(cost);
        tau[to][from] += update_value/(float)(cost);
    }
}

