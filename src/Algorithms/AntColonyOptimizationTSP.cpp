//
// Created by thero on 18.01.2023.
//
#include <AntColonyOptimizationTSP.h>
#include <Utilities.hpp>

AntColonyOptimizationTSP::AntColonyOptimizationTSP
(double _alpha, double _beta) : HeuristicStratTSP{4},
alpha{_alpha}, beta{_beta}, pheromoneLayout{nullptr}
{

}

int AntColonyOptimizationTSP::solve(const std::vector<std::vector<int>> &adj_mat)
{

    size_t cityCount = adj_mat.size();
    /*
     * Mrówki reprezentowane są jako dwie tablice
     * ant_positions - miasto w którym k-ta mrówka się aktualnie znajduje
     * ant_paths - odwiedzone przez mrówkę miasta
     */
    std::vector<int> ant_positions(cityCount);
    intMatrix  ant_paths(cityCount);
    std::vector<int> ant_costs(cityCount);
    floatMatrix pheromones(cityCount);

    int best_cost = INT_MAX;

    /*
     * Ustawiamy feromony na wartość początkową
     */
    this->pheromoneLayout->init(pheromones);

    AntColonyOptimizationTSP::placeAnts(ant_positions);


    for(size_t iteration = 0; iteration < 100; iteration++ )
    {
        for(int i = 0; i < ant_paths.size(); i++)
        {
            ant_paths[i].push_back(i);
        }

        for(int i = 0; i < cityCount ; i++)
        {
            for(size_t j = 0; j < cityCount; j++)
            {
                double prop = 0;
                double x = rand() / (double)RAND_MAX;
                for(size_t k = 0; k < cityCount; k++)
                {
                    if(ant_positions[j] == k)
                        continue;

                    if(std::find(ant_paths[j].begin(), ant_paths[j].end(), k) != ant_paths[j].end())
                        continue;

                    prop += calcPropability(pheromones, ant_paths[j], adj_mat, ant_positions[j], k);

                    if(prop > 0.9999999)
                        prop = 1.0;


                    if(x <= prop)
                    {
                        ant_positions[j] = k;
                        ant_paths[j].push_back(k);
                        break;
                    }
                }
            }
            this->pheromoneLayout->update(pheromones, ant_paths, adj_mat);

            this->pheromoneLayout->evaporate(pheromones);
        }

        placeAnts(ant_positions);
        for(size_t ant = 0; ant < ant_paths.size(); ant++)
        {
            ant_paths[ant].push_back(ant);
        }

        for(size_t i = 0; i < ant_paths.size(); i++)
        {
            int sum = 0;
            for(size_t j = 0; j < ant_paths.size(); j++)
            {
                if(i != ant_paths[i].size()-1)
                    sum += adj_mat[ant_paths[i][j]][ant_paths[i][j+1]];
                else
                    sum += adj_mat[ant_paths[i][j]][0];
            }

            ant_costs[i] = sum;

            best_cost = (sum < best_cost)? sum : best_cost;
        }

        if(ut::getCounter() > 600000)
        {
            printf("\n -> osiagnieto warunek stopu : przekroczono czas wykonywania algorytmu 10 min.");
            return best_cost;
        }

        if(isSinglePath(ant_costs))
        {
            printf("\n -> osiagnieto warunek stopu : uniwersalna sciezka.");
            return best_cost;
        }

        for(auto& path : ant_paths)
        {
            path.clear();
        }
    }

    printf("\n -> osiagnieto warunek stopu : wykonano wszystkie iteracje.");
    return best_cost;
}

void AntColonyOptimizationTSP::placeAnts(std::vector<int> &uh)
{
    for (size_t city_count = 0; city_count < uh.size(); city_count++)
    {
        uh[city_count] = city_count;
    }
}

double AntColonyOptimizationTSP::calcPropability(floatMatrix& tau, std::vector<int>& tabu, const intMatrix& adj_mat, size_t i, size_t j) const
{
    double divider = 0.f;

    for(int k = 0; k < adj_mat.size(); k++)
    {
        if(i == k)
            continue;

        divider += (std::find(tabu.begin(), tabu.end(), k) == tabu.end()) ? (std::pow(tau[i][k], this->alpha) * std::pow(1/((double)(adj_mat[i][k])), this->beta)) : 0;
    }

    return (std::pow(tau[i][j], this->alpha) * std::pow((1/(double)(adj_mat[i][j])), this->beta)) / divider;
}

void AntColonyOptimizationTSP::setAlpha(double alpha)
{
    AntColonyOptimizationTSP::alpha = alpha;
}

void AntColonyOptimizationTSP::setBeta(double beta)
{
    AntColonyOptimizationTSP::beta = beta;
}

bool AntColonyOptimizationTSP::isSinglePath(const std::vector<int> &costs)
{
    int sample = costs[0];
    for(auto &cost : costs)
    {
        if(sample != cost)
            return false;
    }

    printf("\n -> osiagnieto warunek stopu : uniwersalna sciezka.");

    return true;
}
