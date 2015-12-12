#ifndef HOGAR_H
#define HOGAR_H
#include <Objeto.h>

class Hogar: public Objeto
{
    public:
        Hogar(string , float, float, int);
        void quitarVida(int);
        Hogar();
        virtual ~Hogar();
    protected:
    private:
        int vida;
    friend class Juego;
};

#endif // HOGAR_H
