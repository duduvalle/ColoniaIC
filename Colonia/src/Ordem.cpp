#include "Ordem.h"
#include<bits/stdc++.h>
Ordem::Ordem()
{
    //ctor
}

Ordem::~Ordem()
{
    //dtor
}

bool Ordem::sortbysecdesc(const pair<int,float> &a,const pair<int,float> &b)
{
    return a.second>b.second;
}
