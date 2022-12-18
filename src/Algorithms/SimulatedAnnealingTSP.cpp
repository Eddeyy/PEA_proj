//
// Created by thero on 17.12.2022.
//
#include <SimulatedAnnealingTSP.h>
#include <cmath>
#include <Utilities.hpp>

int SimulatedAnnealingTSP::solve(const std::vector<std::vector<int>> &adj_mat)
{
    size_t verticesNumber = adj_mat.size();
    std::vector<int> vertices = getInitialSolution(verticesNumber);

    int cost = calculateCost(adj_mat, vertices);
    double temperature = _startTemperature;

    std::vector<int> bestSolution = vertices;

    int bestCost = cost;

    while (temperature > 1)
    {
        size_t epoch_counter = 1;
        int i = 0;
        while(i < max_epoch)
        {
            std::vector<int> newVertices(vertices);
            changeOrder(newVertices);
            int newCost = calculateCost(adj_mat, newVertices);
            int delta = cost - newCost;

            i++;

            if (delta < 0 && !makeDecision(delta, temperature))
                continue;

            cost = newCost;
            vertices = newVertices;

            if (cost < bestCost)
            {
                bestSolution = vertices;
                bestCost = cost;
            }
        }
        epoch_counter++;
        temperature *= std::pow(_coolingRatio, epoch_counter);
    }

    latest_path = bestSolution;
    return bestCost;
}

int SimulatedAnnealingTSP::calculateCost(const std::vector<std::vector<int>> &adj_mat, std::vector<int> &vertices)
{
    int result = 0;
    int iterations = vertices.size() - 1;

    for(size_t i = 0; i < iterations; i++)
    {
        result += adj_mat[vertices[i]][vertices[i+1]];
    }
    result += adj_mat[vertices[iterations]][vertices[0]];

    return result;
}

double SimulatedAnnealingTSP::calculatePropability(const int delta, const double temperature)
{
    return exp(delta/temperature);
}

bool SimulatedAnnealingTSP::makeDecision(const int delta, const double temperature)
{
    return ut::random() < calculatePropability(delta, temperature);
}

double SimulatedAnnealingTSP::propabilityOnSamples(const int delta, const double temperature, const int samples)
{
    int count = 0;
    for(size_t i = 0; i < samples; i++)
        if(makeDecision(delta, temperature))
            count++;

    return (double)count/samples;
}

void SimulatedAnnealingTSP::changeOrder(std::vector<int> &vertices)
{

    size_t first = rand() % vertices.size();
    size_t second =  rand() % vertices.size();
    std::swap(vertices[first], vertices[second]);
}

std::vector<int> SimulatedAnnealingTSP::getInitialSolution(size_t verticesNumber)
{
    std::vector<int> vertices;
    for(size_t i = 0; i < verticesNumber; i++)
        vertices.push_back(i);
    for(size_t i = 0; i < verticesNumber; i++)
        changeOrder(vertices);

    return vertices;
}

void SimulatedAnnealingTSP::setMaxEpoch(size_t maxEpoch)
{
    max_epoch = maxEpoch;
}
