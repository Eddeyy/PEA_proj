//
// Created by thero on 20.01.2023.
//

#include <QAS.h>

void QAS::update(floatMatrix &tau, intMatrix &paths, const intMatrix& adj_mat)
{
    float update_value = 10.f;

    for(auto & path : paths)
    {
        int from = path[path.size()-2];
        int to = path[path.size()-1];

        tau[from][to] += update_value/(float)(adj_mat[from][to]);
        tau[to][from] += update_value/(float)(adj_mat[from][to]);
    }
}

