#include <iostream>
#include "Solucao.h"
#include "Grafo.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
#include "Input.h"

using namespace std;

void Iimprime(vector<vector<int> >gr)
{
    cout << endl << "{";
    for(unsigned int i = 0; i<gr.size(); i++)
    {
        cout << "{";
        for (unsigned int j = 0; j<gr[i].size(); j++)
        {
                if(j == gr[i].size()-1)
                    cout << gr[i][j];
                else
                    cout << gr[i][j] << ", ";

        }
        if(i == gr.size()-1)
            cout << "}";
        else
            cout <<"}, ";

    }
    cout << "}" << endl;
}

int main(int argc, char **argv)
{
    int cont=0;
    time_t timeStart;
    vector <int> cand;
    double tim = 0;
    srand (time(NULL));
    int type = atoi(argv[2]);
    string path = argv[1];
    Input i;
    i.readInstance(path,type);
    tim = 0;
    timeStart = clock();
    while(tim<60)
    {
        for(int c = 0; c<5; c++)
        {
            cand.clear();
            cand = i.s->construirInicial();
            i.construtivo(cand,c);
            i.buscaLocal(c);
        }
        i.s->melhorTodos();
        i.s->buscaLocalM();
        i.s->evapora();
        i.s->atualizar();
        i.s->Clear();
        tim = (double)((clock() - timeStart) / CLOCKS_PER_SEC);
        cont++;
    }
    cout << i.s->calculo(i.s->melhorT) <<" "<<cont<< endl;
    Iimprime(i.s->melhorT);
    cout << endl <<i.s->verificarSolucao(i.s->melhorT);
    return 0;
}
