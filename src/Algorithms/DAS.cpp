//
// Created by thero on 19.01.2023.
//
#include <DAS.h>

void DAS::update(float** tau, int** paths, const intMatrix& adj_mat, size_t& cityCount, size_t curCity)
{
    float update_value = 10.f;

    for(size_t path = 0; path < cityCount; path++)
    {
        int from = paths[path][curCity-1];
        int to = paths[path][curCity];

        tau[from][to] += update_value;
        tau[to][from] += update_value;

    }

}