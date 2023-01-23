//
// Created by thero on 20.01.2023.
//

#include <QAS.h>

void QAS::update(float** tau, int** paths, const intMatrix& adj_mat, size_t& cityCount, size_t curCity)
{
    float update_value = 10.f;

    for(size_t path = 0; path < cityCount; path++)
    {
        int from = paths[path][curCity-1];
        int to = paths[path][curCity];

        double cost = (adj_mat[from][to] == 0)? 0.1 : adj_mat[from][to];

        tau[from][to] += update_value/(float)(cost);
        tau[to][from] += update_value/(float)(cost);
    }
}

