//
// Created by thero on 15.10.2022.
//
#include <BruteForceTSP.hpp>
#include <bits/stdc++.h>

int BruteForceTSP::solve(const std::vector<std::vector<int>> &adj_mat)
{
    std::vector<int> vertex;

for(int i = 1; i < adj_mat.size(); i++)
        vertex.emplace_back(i);         //Dodajemy wszystkie wierzchołki w grafie, aby następnie
                                        //skorzystać z permutacji, aby zbadać wszystkie dostępne
                                        //kolejności odwiedzania wierzchołków

int minimal_path = INT_MAX;             //Jako że mamy do czynienia z problemem minimalizacyjnym
                                        //ustawiamy wstępną wartość na największą dostępną w zakresie

    this->latest_path = vertex;                 //Aby zapamiętać optymalną ścieżkę przypisujemy aktualną permutację
                                                //wierzchołków do tablicy w klasie strategii

    do
    {
        int current_weight = 0;                 //Zaczynając "przejście" po grafie ustawiamy koszt obecnej
                                                //ścieżki jako zerowy

        int k = 0;                              //Zakładamy, że zawsze zaczynamy z wierzchołka zerowego

        for(int i : vertex)
        {                                       //Przemieszczamy się po grafie zgodnie z obecną permutacją
            current_weight += adj_mat[k][i];    //przechowywaną w zmiennej vertex dodając wagi przejść do kosztu całkowitego
            k = i;                              //Po odwiedzeniu wierzchołka ustawiamy obecny, na ten odwiedzony
        }
        current_weight += adj_mat[k][0];        //Wracając do punktu wyjścia również dodajemy koszt przejścia

        if(minimal_path > current_weight)
        {                                       //Jeżeli koszt całkowity obecnego przejścia jest mniejszy od
            this->latest_path = vertex;         //kosztu poprzedniego, przypisujemy go do zmiennej, oraz zapisujemy
            minimal_path = current_weight;      //aktualną permutację w polu klasy strategii
        }

    }
    while(std::next_permutation(vertex.begin(),vertex.end()));  //Wykonujemy powyższy algorytm do póki istnieją kolejne
                                                                //kombinacje zestawu wierzchołków

    return minimal_path;
}