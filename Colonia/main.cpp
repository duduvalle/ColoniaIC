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

int main()
{
    time_t timeStart;
    vector <int> cand;
    double tim = 0;
    srand (time(NULL));
    int type = 2;
    string path = "instancias-Grupos/TipoD/20_5_A.txt";
    Input i;
    i.readInstance(path,type);
    for(int g = 0; g < 10; g++)
    {
        for(int c = 0; c<5; c++)
        {
            cand.clear();
            cand = i.s->construirInicial();
            i.construtivo(cand,c);
            i.buscaLocal(c);
        }
        i.s->melhorTodos();
        i.s->evapora();
        i.s->atualizar();
        i.s->Clear();
    }
    timeStart = clock();
    tim = (double)((clock() - timeStart) / CLOCKS_PER_SEC);
    cout << i.s->calculo(i.s->melhorT) << endl;
    cout << tim << endl;
    Iimprime(i.s->melhorT);
    return 0;
}
