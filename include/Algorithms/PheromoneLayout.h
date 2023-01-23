//
// Created by thero on 18.01.2023.
//

#ifndef TSP_BF_PHEROMONELAYOUT_H
#define TSP_BF_PHEROMONELAYOUT_H
#include <iostream>
#include <vector>

class PheromoneLayout
{
protected:
    using intMatrix = std::vector<std::vector<int>>;
    using floatMatrix = std::vector<std::vector<float>>;

public:
    virtual void update(float** tau, int** paths, const intMatrix& adj_mat, size_t& cityCount, size_t curCity) = 0;
    virtual void init(float** tau, size_t  &cityCount)
    {
        for (int city_from = 0; city_from < cityCount; city_from++)
        {
            for (size_t city_to = 0; city_to < cityCount; city_to++)
            {
                tau[city_from][city_to]+=0.01f;
            }
        }
    };

    virtual void evaporate(float** tau, size_t size)
    {
        for (size_t from = 0; from < size; from++)
        {
            for(size_t to = 0; to < size; to++)
            {
                tau[from][to] = (tau[from][to] * 0.5) < 0.005 ? 0.005 : (tau[from][to] * 0.5) ;
            }
        }
    }
    virtual ~PheromoneLayout()= default;
};

#endif //TSP_BF_PHEROMONELAYOUT_H
