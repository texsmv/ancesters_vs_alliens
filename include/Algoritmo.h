#ifndef ALGORITMO_H
#define ALGORITMO_H


class Algoritmo
{
    public:
        Algoritmo(float*,float*,int,int,int);
        float getprobabilidad(float*,float*);
        int factorial(int);
        void setproba(float);
        bool siono();
        float combinatoria(int, int);
        virtual ~Algoritmo();
    protected:
    private:
        float probabilidad;
        float *valores;
        float *pesos;
        int numvalores;
        float combinator;

};

#endif // ALGORITMO_H
