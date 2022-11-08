//
// Created by thero on 06.11.2022.
//
#include <Algorithms/HeldKarpTSP.h>
#include <algorithm>
#include <Utilities.hpp>

int HeldKarpTSP::solve(const std::vector<std::vector<int>> &adj_mat)
{
    std::vector<std::pair<int,bool>> remaining;
    latest_path.clear();
    for(int i = 0; i < adj_mat.size(); i++)
    {
        remaining.emplace_back(std::pair<int,bool>(i,false));
        latest_path.emplace_back(i);
    }
    remaining[0].second = true;

    auto result = heldKarp(0, remaining, INT32_MAX, 0, adj_mat);
    return result;
}

int HeldKarpTSP::heldKarp(int currentVertex, std::vector<std::pair<int, bool>> remainingVertices, int shortestPath,
                          int currentPath, const std::vector<std::vector<int>> &adj_mat, int rec)
{
//    auto it = valid_vertices.find(currentVertex);
//    if(it == valid_vertices.end())
//        valid_vertices.insert(std::make_pair(rec, currentVertex));
//    else
//    {
//        valid_vertices.at(rec) = currentVertex;
//    }

    if(!ut::findInPairVector(remainingVertices,false))
    {
        latest_path[latest_path.size()-1] = currentVertex;
        return currentPath + adj_mat[currentVertex][0];
    }
    else
    {

        for(int i = 0 ; i < remainingVertices.size(); i++){
            if(!(remainingVertices[i].second))
            {
                if(currentPath + adj_mat[currentVertex][i] < shortestPath)
                {
                    remainingVertices[i].second = true;
                    int result = heldKarp(i, remainingVertices, shortestPath,currentPath + adj_mat[currentVertex][i], adj_mat, rec + 1);
                    if(result < shortestPath)
                    {
                        latest_path[rec + 1] = i;
                        shortestPath = result;
                    }

                    remainingVertices[i].second = false;
                }
            }
        }
        return shortestPath;
    }
}
