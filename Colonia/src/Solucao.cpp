#include "Solucao.h"
#include "Grafo.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

Solucao::Solucao(int nn, int ng, float h, float l)
{
    high = h;
    lower = l;
    numeroG = ng;
    g = new Grafo(nn);
    for (int j = 0; j < 5; j++)
    {
        vector <vector<int> >gruposs;
        for(int i = 0; i < numeroG; i++)
        {
            vector<int> grupo;
            grupo.clear();
            gruposs.push_back(grupo);
        }
        grupos.push_back(gruposs);
        best.push_back(gruposs);
    }
    for(int i = 0; i < numeroG; i++)
    {
        vector<int> grupo;
        grupo.clear();
        inicial.push_back(grupo);
    }
}

Solucao::~Solucao()
{
    delete g;
}

void Solucao::evapora()
{
    int n = GetnumeroVe();
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            setFe(i,j,getFe(i,j)*0.95);
            if(getFe(i,j)<100)
            {
                setFe(i,j,100);
            }
        }
    }
}

void Solucao::atualizar()
{
    float x,y;
    float m = calculo(melhorT);
    for (unsigned int w = 0; w<best.size(); w++)
    {
        for (unsigned int i = 0; i<best[w].size(); i++)
        {
            for (unsigned int j = 0; j<best[w][i].size(); j++)
            {
                for (unsigned int k = j+1; k<best[w][i].size();k++)
                {
                    x = m/calculo(best[w]);
                    y = getFe(best[w][i][j],best[w][i][k]) + x;
                    g->setF(best[w][i][j],best[w][i][k],y);
                    g->setF(best[w][i][k],best[w][i][j],y);
                    if(getFe(best[w][i][j],best[w][i][k])>1000)
                    {
                        g->setF(best[w][i][j],best[w][i][k],1000);
                        g->setF(best[w][i][k],best[w][i][j],1000);
                    }
                }
            }

        }
    }
}

float Solucao::calculo(vector<vector<int> >gr)
{
    float soma = 0;
    for(int i = 0; i<numeroG; i++)
    {
        unsigned int h = gr[i].size();
        for (unsigned int j = 0; j<h; j++)
        {
            for (unsigned int k = j+1; k<h; k++)
            {
                soma += getMa(gr[i][j],gr[i][k]);
            }
        }
    }
    return soma;

}

bool sortbysecdesce(const pair<int,float> &a,
                   const pair<int,float> &b)
{
       return a.second>b.second;
}

void Solucao::buscaLocal (int conjuntoF)
{
    if (conjuntoF>=0 && conjuntoF<5)
    {
        grupos[conjuntoF] = best[conjuntoF];
        unsigned int quantGrupos = grupos[conjuntoF].size();
        vector<int> cand;
        for(unsigned int grupo = 0;grupo < quantGrupos;grupo++)
        {
            int k;
            if(grupos[conjuntoF][grupo].size() != 0)
            {
                k = rand()%grupos[conjuntoF][grupo].size();
                int no = grupos[conjuntoF][grupo][k];
                grupos[conjuntoF][grupo].erase(grupos[conjuntoF][grupo].begin()+k);
                cand.push_back(no);
            }
        }

        unsigned int sizeCand = cand.size();
        vector < pair <int,float> > candOrdenar;
        for (unsigned int i = 0; i < sizeCand; i++)
        {
            candOrdenar.push_back(make_pair(cand[i],g->getV(cand[i])));
        }
        sort(candOrdenar.begin(), candOrdenar.end(), sortbysecdesce);
        cand.clear();
        for (unsigned int i = 0; i < sizeCand; i++)
        {
            cand.push_back(candOrdenar[i].first);
        }

        for (unsigned int p = 0;p < sizeCand; p++)
        {
            int can = cand[p];
            int melhorGrupo;
            float aux;
            float maior = 0;
            for (unsigned int grupo = 0; grupo<quantGrupos; grupo++)
            {
                float f=0;
                aux=0;
                for (unsigned int noG = 0; noG<grupos[conjuntoF][grupo].size(); noG++)
                {
                    f += getVe(grupos[conjuntoF][grupo][noG]);
                    aux += getMa(grupos[conjuntoF][grupo][noG],can);
                }
                if (f+getVe(can)<=high)
                {
                    if(aux>=maior)
                    {
                        maior = aux;
                        melhorGrupo = grupo;
                    }
                }
            }
            grupos[conjuntoF][melhorGrupo].push_back(can);
        }

        if(calculo(grupos[conjuntoF])> calculo(best[conjuntoF]))
            best[conjuntoF] = grupos[conjuntoF];
    }
}

vector <int> Solucao::construirInicial()
{
    for (int z = 0; z < numeroG; z++)
        inicial[z].clear();
    vector <int> cand = g->Candidatos();
    for(int k = 0; k<numeroG; k++)
    {
        int i = rand()%cand.size();
        inicial[k].push_back(cand[i]);
        cand.erase(cand.begin()+i);
        while (verificaGrupoInicial(k)<lower)
        {
            BestVG(cand,k);
        }
    }
    return cand;
}

float Solucao::verificaGrupoInicial(int gru)
{
    float soma = 0;
    for (unsigned int j = 0; j<inicial[gru].size(); j++)
    {
        soma += getVe(inicial[gru][j]);
    }
    return soma;
}

void Solucao::BestVG(vector<int> &cand, int gru)
{
    int i = 0;
    float aux = 0;
    float maior = 0;
    for (unsigned int j = 0; j<cand.size(); j++)
    {
        aux = CalculoGV(gru,cand[j]);
        if(aux>maior && verificaGrupoInicial(gru)+getVe(cand[j])<=high)
        {
            maior = aux;
            i=j;
        }
    }
    inicial[gru].push_back(cand[i]);
    cand.erase(cand.begin()+i);
}

float Solucao::CalculoGV(int j, int v)
{
    float soma = 0;
    for(unsigned int i = 0; i<inicial[j].size(); i++)
    {
        soma += getMa(inicial[j][i],v);
    }
    return soma;
}

void Solucao::contruirFormiga(vector <int> cand, int conjuntoF)
{
    vector <float> ferV;
    vector <int> qualGrupo;
    for(int a = 0; a <numeroG; a++ )
        grupos[conjuntoF][a].clear();
    grupos[conjuntoF] = inicial;
    for (unsigned int i = 0; i < cand.size(); i++)
    {
        ferV.clear();
        qualGrupo.clear();
        int can = cand[i];
        for (int grupo = 0; grupo< numeroG; grupo++)
        {
            float f=0;
            float aux=0;
            for (unsigned int noG = 0; noG<grupos[conjuntoF][grupo].size(); noG++)
            {
                f += getVe(grupos[conjuntoF][grupo][noG]);
                aux += getFe(grupos[conjuntoF][grupo][noG],can);
            }
            if(f+getVe(can)<=high)
            {
                if(qualGrupo.size()>0)
                {
                    ferV.push_back(aux + ferV[grupo-1]);
                }
                else
                {
                    ferV.push_back(aux);
                }
                qualGrupo.push_back(grupo);
            }
        }
        float maior = ferV.back();
        int rando = rand()%int(maior);
        cout <<" " <<int(maior) <<" ";
        for(unsigned int r = 0; r < qualGrupo.size() ; r++)
        {
            if(rando <= ferV[r])
            {
                grupos[conjuntoF][qualGrupo[r]].push_back(can);
                break;
            }
        }
    }
    cout << " eita ";
    if(calculo(grupos[conjuntoF])> calculo(best[conjuntoF]))
        best[conjuntoF] = grupos[conjuntoF];
    cout << calculo(grupos[conjuntoF]) << " " << calculo(best[conjuntoF]) << endl;
}

void Solucao::Clear()
{
    for (int i = 0; i < 5; i++)
        for(int a = 0; a <numeroG; a++ )
            best[i][a].clear();
}

void Solucao::melhorTodos ()
{
    for (int i = 0; i < 5; i++)
        if(calculo(best[i])> calculo(melhorT))
            melhorT = best[i];
}
