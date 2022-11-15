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
    /*
     * Jeśli wszystkie wierzchołki tablicy zostały odwiedzone, nalezy zwrócić obecną wartość kosztu ścieżki,
     * a następnie dodać do tego koszt powrotu do wierchołka startowego.
     * */
    if(std::find(remainingVertices.begin(),remainingVertices.end(),false) == remainingVertices.end())
    {
        return currentPath + adj_mat[currentVertex][0];
    }
        /*
         * Rozpatrzeć wszystkie wierchołki sąsiadujące z obecnym.
         * */
        for(int i = 0 ; i < remainingVertices.size(); i++)
        {
            /*
             * Sprawdzenie, czy rozpatrywany wierchołek nalezy do nieodwiedzonych
             * */
            if (!(remainingVertices[i]))
            {
                /*
                 * Należy sprawdzić, czy obecne rozwiązanie danego podproblemu nie jest już większe od globalnie najkrótszej ścieżki
                 * */
                if (currentPath + adj_mat[currentVertex][i] < shortestPath)
                {
                    /*
                     * Jeżeli nie jest, ustawić rozpatrywany wierchołek jako odwiedzony,
                     * a nastepnie wykonać analogiczną procedurę dla aktualnie rozpatrywanego wierzchołka
                     * i przypisać otrzymane rozwiązanie podproblemu do zmiennej
                     */
                    remainingVertices[i] = true;
                    int result = heldKarp(i, remainingVertices, shortestPath, currentPath + adj_mat[currentVertex][i],
                                          adj_mat, rec + 1);
                    /*
                     * Jeżeli rozwiązanie podproblemu jest mniejsze od obecnego globalnie minimalnego rozwiązania
                     */
                    if (result < shortestPath)
                    {
                        /*
                         * Wstawić obecny wierchołek w tablicy finalnej ścieżki na elemencie o indeksie równym obecnemu
                         * poziomowi rekurencji + 1 i przypisać globalnie minimalnemu rozwiązaniu wynik wywołania rekursywnego
                         */
                        latest_path[rec + 1] = i;
                        shortestPath = result;
                    }
                    /*
                     * Ustawić własnie rozpatrzony wierchołek, spowrotem jako odwiedzony
                     * aby umożliwić rozpatrzenie go jako podproblemu dla kolejnego sąsiada obecnego wierchołka
                     */
                    remainingVertices[i] = false;
                }
            }
        }
        // Zwrócić globalnie minimalne rozwiązanie
        return shortestPath;
}
