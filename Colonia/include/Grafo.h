#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
using namespace std;

class Grafo
{
    public:
        Grafo(int val);
        virtual ~Grafo();

        float getM(int i, int j) { return mat[i][j]; }
        void setM(int i, int j, float val) { mat[i][j] = val; }

        float getF(int i, int j) { return fer[i][j]; }
        void setF(int i, int j, float val) { fer[i][j] = val; }

        float getV(int i) { return vet[i]; }
        void setV(int i, float val) { vet[i] = val; }

        int GetnumeroNos() { return numeroNos; }
        void SetnumeroNos(int val) { numeroNos = val; }

        void Ordenar();
        vector <int> Candidatos();

    private:
        int numeroNos;
        float **mat;
        float *vet;
        float **fer;
        vector < pair <int,float> > cand;
};

#endif // GRAFO_H
