#include "Algoritmo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
Algoritmo::Algoritmo(float* valo, float* peso,int tamano,int tam_venta,int num_naves)
{
    this->valores=valo;
    this->pesos=peso;
    this->numvalores=tamano;
    this->combinator=combinatoria(tam_venta,num_naves);

}
int Algoritmo::factorial(int a)
{
    int fac=1;
    for (int i=1;i<a;i++)
    {
        fac=fac*i;
    }
    return fac;
}
float Algoritmo::combinatoria(int a, int b)
{
    return Algoritmo::factorial(a)/(Algoritmo::factorial(b)*Algoritmo::factorial(a-b));
}
void Algoritmo::setproba(float num)
{
    this->probabilidad=num;
}
float Algoritmo::getprobabilidad(float* valors,float*pesos)
{
    float promedio=0;
    for (int i=0;i<numvalores;i++)
    {
        promedio=promedio+valors[i]/pesos[i];
    }
    promedio=promedio/numvalores;
    probabilidad=promedio/combinator;
    return probabilidad;
}

bool Algoritmo::siono()
{
    srand(time(NULL));
    int num=rand()%100;
    std::cout<<num<<"-->";
    if (num<=probabilidad)
        return true;
    else
        return false;
}
Algoritmo::~Algoritmo()
{
    //dtor
}
