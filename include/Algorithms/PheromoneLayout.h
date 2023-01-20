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
    virtual void update(floatMatrix &tau, intMatrix& paths, const intMatrix& adj_mat) = 0;
    virtual void init(std::vector<std::vector<float>> &tau)
    {
        for (auto &city_from : tau)
        {
            for (size_t city_to = 0; city_to < tau.size(); city_to++)
            {
                city_from.push_back(0.01f);
            }
        }
    };

    virtual void evaporate(floatMatrix &tau)
    {
        for (auto& from: tau)
        {
            for(auto& to: from)
            {
                to = (to * 0.5) < 0.005 ? 0.005 : (to * 0.5) ;
            }
        }
    }
    virtual ~PheromoneLayout()= default;
};

#endif //TSP_BF_PHEROMONELAYOUT_H
