#include "Grafo.h"
#include<bits/stdc++.h>
#include <vector>
using namespace std;

Grafo::Grafo(int val)
{
    SetnumeroNos(val);
    vet = new float[val];
    mat = new float*[val];
    for(int i = 0; i < val; i++)
        mat[i] = new float[val];
    fer = new float*[val];
    for(int i = 0; i < val; i++)
        fer[i] = new float[val];
    for(int i = 0; i < val; i++)
        for(int j = 0; j < val; j++)
            fer[i][j]=1000;
    Ordenar();
}


Grafo::~Grafo()
{
    for(int i = 0; i < numeroNos; i++)
        delete [] mat[i];
    delete [] mat;
    for(int i = 0; i < numeroNos; i++)
        delete [] fer[i];
    delete [] fer;
    delete [] vet;
}

bool sortbysecdesc(const pair<int,float> &a,
                   const pair<int,float> &b)
{
       return a.second>b.second;
}

void Grafo::Ordenar()
{
    for (int i=0; i<numeroNos; i++)
        cand.push_back( make_pair(i,vet[i]) );
    sort(cand.begin(), cand.end(), sortbysecdesc);
}

vector <int> Grafo::Candidatos()
{
    vector <int> x;
    for (int i=0; i<numeroNos; i++)
        x.push_back(cand[i].first);
    return x;
}
