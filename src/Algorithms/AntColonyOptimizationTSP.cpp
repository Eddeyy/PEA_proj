//
// Created by thero on 18.01.2023.
//
#include <AntColonyOptimizationTSP.h>
#include <Utilities.hpp>
#include <QAS.h>

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
    int* ant_positions;
    int**  ant_paths;
    int* ant_costs;
    float** pheromones;

    ant_positions = new int[cityCount];

    ant_paths = new int*[cityCount];
    for(int i = 0; i < cityCount; i++)
    {
        ant_paths[i] = new int[cityCount+1];
        for(int j = 0; j < cityCount+1; j++)
        {
            ant_paths[i][j] = -1;
        }
    }

    ant_costs = new int[cityCount];

    pheromones = new float*[cityCount];
    for(int i = 0; i < cityCount; i++)
    {
        pheromones[i] = new float[cityCount];
    }

    int best_cost = INT_MAX;

    /*
     * Ustawiamy feromony na wartość początkową
     */
    this->pheromoneLayout->init(pheromones, cityCount);

    AntColonyOptimizationTSP::placeAnts(ant_positions, cityCount);


    for(size_t iteration = 0; iteration < 2000; iteration++ )
    {
        /*
         * Wstaw pierwsze miasto na początek ścieżki każdej z mrówek.
         */
        for(int i = 0; i < cityCount; i++)
        {
            ant_paths[i][0] = i;
        }

        for(size_t i = 0; i < cityCount ; i++)
        {
            for(size_t j = 0; j < cityCount; j++)
            {
                double prop = 0.0;
                double x = ut::random();

                if(x > 1.0)
                    x = 1.0;

                for(size_t k = 0; k < cityCount; k++)
                {
                    if(!arrayContains(ant_paths[j], cityCount+1, k))
                        prop += calcPropability(pheromones, ant_paths[j], adj_mat, ant_positions[j], k);
                    if(prop > 0.999)
                        prop = 1.0;

                    if(x <= prop)
                    {
                        ant_positions[j] = k;
                        ant_paths[j][i + 1] = k;
                        break;
                    }
                }
            }
            if(i == cityCount-1)
            {
                placeAnts(ant_positions, cityCount);
                for (size_t ant = 0; ant < cityCount; ant++)
                {
                    ant_paths[ant][cityCount] = ant;
                }
            }
            this->pheromoneLayout->update(pheromones, ant_paths, adj_mat, cityCount, i+1);

            this->pheromoneLayout->evaporate(pheromones, cityCount);
        }


        for(size_t i = 0; i < cityCount; i++)
        {
            int sum = 0;
            for(size_t j = 0; j < cityCount; j++)
            {
                sum += adj_mat[ant_paths[i][j]][ant_paths[i][j+1]];
            }

            ant_costs[i] = sum;

            best_cost = (sum < best_cost)? sum : best_cost;
        }

        if(ut::getCounter() > 600000)
        {
            printf("\n -> osiagnieto warunek stopu : przekroczono czas wykonywania algorytmu 10 min.");
            deleteMat(ant_paths, cityCount);
            deleteMat(pheromones, cityCount);
            delete [] ant_positions;
            delete [] ant_costs;
            return best_cost;
        }

        if(isSinglePath(ant_costs, cityCount))
        {

            printf("\n -> osiagnieto warunek stopu : uniwersalna sciezka.");
            deleteMat(ant_paths, cityCount);
            deleteMat(pheromones, cityCount);
            delete [] ant_positions;
            delete [] ant_costs;
            return best_cost;
        }


        for(int i = 0; i < cityCount; i++)
        {
            for(int j = 0; j < cityCount; j++)
            {
                ant_paths[i][j] = -1;
            }
        }
    }

    printf("\n -> osiagnieto warunek stopu : wykonano wszystkie iteracje.");

    deleteMat(ant_paths, cityCount);
    deleteMat(pheromones, cityCount);
    delete [] ant_positions;
    delete [] ant_costs;
    return best_cost;
}

void AntColonyOptimizationTSP::placeAnts(int* uh, size_t &cityCount)
{
    for (size_t city_count = 0; city_count < cityCount; city_count++)
    {
        uh[city_count] = city_count;
    }
}

double AntColonyOptimizationTSP::calcPropability(float** tau, const int* tabu, const intMatrix& adj_mat, size_t i, size_t j) const
{
    double divider = 0.0;

    for(int k = 0; k < adj_mat.size(); k++)
    {

        double visibility_divider = (adj_mat[i][k] == 0)? 1/0.1 : 1/(static_cast<double>(adj_mat[i][k]));
        auto divider_add = (std::pow(tau[i][k], this->alpha) * std::pow(visibility_divider, this->beta));
        divider += arrayContains(tabu, adj_mat.size()+1, k) ? 0.0 : divider_add ;
    }


    double result = (std::pow(tau[i][j], this->alpha) * std::pow((1/static_cast<double>(adj_mat[i][j])), this->beta)) / divider;
    return result;
}

void AntColonyOptimizationTSP::setAlpha(double alpha)
{
    AntColonyOptimizationTSP::alpha = alpha;
}

void AntColonyOptimizationTSP::setBeta(double beta)
{
    AntColonyOptimizationTSP::beta = beta;
}

bool AntColonyOptimizationTSP::isSinglePath(const int* costs, size_t& citycount)
{
    int sample = costs[0];
    for(int i = 0 ; i < citycount; i++)
    {
        if(sample != costs[i])
            return false;
    }

    return true;
}

void AntColonyOptimizationTSP::deleteMat(int** mat, size_t& size)
{
    for(size_t i = 0; i < size; i++)
    {
        delete [] mat[i];
    }
    delete [] mat;
}

void AntColonyOptimizationTSP::deleteMat(float** mat, size_t& size)
{
    for(size_t i = 0; i < size; i++)
    {
        delete [] mat[i];
    }
    delete [] mat;
}

bool AntColonyOptimizationTSP::arrayContains(const int* const arr, const size_t& arrSize, int val)
{
    for(size_t i = 0; i < arrSize; i++)
    {
        if(arr[i] == val)
            return true;
    }
    return false;
}
