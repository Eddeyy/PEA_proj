//
// Created by thero on 06.11.2022.
//
#include <Algorithms/HeldKarpTSP.h>
#include <algorithm>
#include <Utilities.hpp>

int HeldKarpTSP::solve(const std::vector<std::vector<int>> &adj_mat)
{
    std::vector<bool> remaining;
    latest_path.clear();
    for(int i = 0; i < adj_mat.size(); i++)
    {
        remaining.emplace_back(false);
        latest_path.emplace_back(i);
    }
    remaining[0] = true;

    auto result = heldKarp(0, remaining, INT32_MAX, 0, adj_mat);
    return result;
}

int HeldKarpTSP::heldKarp(int currentVertex, std::vector<bool> remainingVertices, int shortestPath,
                          int currentPath, const std::vector<std::vector<int>> &adj_mat, int rec)
{
    int result;

    if(std::find(remainingVertices.begin(), remainingVertices.end(),false) == remainingVertices.end())
        return currentPath + adj_mat[currentVertex][0];

    for(int i = 0 ; i < remainingVertices.size(); i++)
    {
        if(!(remainingVertices[i]))
        {
            if(currentPath + adj_mat[currentVertex][i] < shortestPath)
            {
                remainingVertices[i] = true;
                result = heldKarp(i, remainingVertices, shortestPath,currentPath + adj_mat[currentVertex][i], adj_mat, rec + 1);
                if(result < shortestPath)
                {
                    latest_path[rec + 1] = i;
                    shortestPath = result;
                }
                remainingVertices[i] = false;
            }
        }
    }

        return shortestPath;
}
