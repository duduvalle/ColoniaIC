#ifndef SOLUCAO_H
#define SOLUCAO_H
#include "Grafo.h"
#include <vector>
using namespace std;

class Solucao
{
    public:
        Solucao(int nn, int ng, float h, float l);
        virtual ~Solucao();

        void evapora();
        void atualizar();
        void contruirFormiga(vector <int> cand, int conjuntoF);

        float calculo(vector<vector<int> >gr);
        void buscaLocal(int conjuntoF);
        void buscaLocalM();
        void nova();
        vector <int> construirInicial();
        float CalculoGV(int j, int v);
        void BestVG(vector<int> &cand, int gru);
        float verificaGrupoInicial(int gru);
        void Clear();
        void melhorTodos();
        bool verificarSolucao(vector<vector<int> >gr);

        float getFe(int i, int j) { return g->getF(i,j); }
        void setFe(int i, int j, float val) { g->setF(i,j,val); }

        float getMa(int i, int j) { return g->getM(i,j); }
        void setMa(int i, int j, float val) { g->setM(i,j,val); }

        float getVe(int i) { return g->getV(i); }
        void setVe(int i, float val) { g->setV(i,val); }

        int GetnumeroVe() { return g->GetnumeroNos(); }
        void SetnumeroVe(int val) { g->SetnumeroNos(val); }

        vector <vector<vector<int> > >grupos;
        vector <vector<vector<int> > >best;
        vector <vector<int> >inicial;
        vector <vector<int> >melhorT;
    private:
        float high, lower;
        int numeroG;
        Grafo *g;

};

#endif // SOLUCAO_H
